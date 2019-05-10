/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:57:21 by myaremen          #+#    #+#             */
/*   Updated: 2019/04/26 07:54:57 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	players_sort_by_id(t_player *players, uint32_t nplayers)
{
	(void)players;
	(void)nplayers;
}

uint32_t player_threads_alive(t_player *player)
{
	size_t thread;
	uint32_t alive;

	alive = 0;
	thread = 0;
	while (thread < threads_size(&player->threads))
	{
		if (threads_at(&player->threads, thread)->alive)
		{
			++alive;
		}
		++thread;
	}
	return (alive);
}

uint32_t threads_alive(t_player *players, uint32_t nplayers)
{
	uint32_t player;
	uint32_t alive;

	player = 0;
	alive = 0;
	while (player < nplayers)
	{
		alive += player_threads_alive(&players[player]);
		++player;
	}
	return (alive);
}

void    kill_thread_if_no_lives(t_thread *th)
{
	if (th->lives == 0)
	{
		th->alive = 0;
	}
	else
	{
		th->lives = 0;
	}
}

void    foreach_thread(t_player *players, uint32_t nplayers, void(*func)(t_thread*))
{
	uint32_t player;
	uint32_t player_thread;

	player = 0;
	while (player < nplayers)
	{
		player_thread = 0;
		while (player_thread < threads_size(&players[player].threads))
		{
			func(threads_at(&players[player].threads, player_thread));
			++player_thread;
		}
		++player;
	}
}

void	vm_cycle(t_player *players, uint32_t nplayers)
{
	uint32_t cycles;
	uint32_t cycles_to_die;
	uint32_t checks;
	uint32_t alive;

	cycles = 0;
	cycles_to_die = CYCLE_TO_DIE;
	checks = 0;
	while ((alive = threads_alive(players, nplayers)))
	{
		if (checks == MAX_CHECKS || alive > 21)
		{
			cycles_to_die -= CYCLE_DELTA;
			checks = 0;
		}
		++checks;
		foreach_thread(players, nplayers, op_exec);
		++cycles;
		if (cycles == cycles_to_die)
        {
			foreach_thread(players, nplayers, kill_thread_if_no_lives);
		    cycles = 0;
        }
	}
}

t_opcode decode_opcode(struct s_thread *pc)
{
	t_opcode opcode;

	opcode = as_byte(pc->vm_memory)[pc->ip % MEM_SIZE];
	if (opcode < oplowborder || opcode >= ophighborder)
	{
		pc->alive = 0;
		return (opcode);
	}
	pc->ip += 1;
	return (opcode);
}

bool	check_op_params(t_opcode opcode, uint8_t tparams)
{
	if ((op_tab[opcode].targs[0] & (tparams >> 6)) == 0)
	{
		return (0);
	}
	else if ((op_tab[opcode].targs[1] & (tparams  >> 4)) == 0)
	{
		return (0);
	}
	else if ((op_tab[opcode].targs[2] & (tparams >> 2)) == 0)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

uint8_t	decode_tparams(struct s_thread *pc, t_opcode opcode)
{
	uint8_t tparams;

	if ((op_tab[opcode].targs[0] & T_IND) || (op_tab[opcode].targs[1] & T_IND) || (op_tab[opcode].targs[2] & T_IND))
	{
		tparams = as_byte(pc->vm_memory)[pc->ip % MEM_SIZE];
		if (!check_op_params(opcode, tparams))
		{
			pc->alive = 0;
			return (tparams);
		}
		pc->ip += 1;
	}
	else
	{
		tparams = (op_tab[opcode].targs[0] << 6) | (op_tab[opcode].targs[1] << 4) | (op_tab[opcode].targs[2] << 2);
	}
	return (tparams);
}

uint32_t swap32(uint32_t *toswap)
{
	return (*toswap >> 24 | ((*toswap >> 8) & 0xff00 ) | ((*toswap << 8) & 0xff0000 ) | *toswap << 24);
}


uint16_t swap16(uint16_t *toswap)
{
	return (*toswap >> 8 | *toswap << 8);
}

t_memory decode_param(t_opcode opcode, uint8_t tparams, t_thread *pc, uint8_t param_number)
{
	t_memory param;
	uint8_t  tparam;
	uint8_t reg_number;

	memory_init(&param, 0, 0);
	if (param_number <= op_tab[opcode].args)
	{
		if (param_number == 1)
		{
			tparam = ((tparams & T_FIRST_PARAM) >> 6) & 0x3;
		}
		else if (param_number == 2)
		{
			tparam = ((tparams & T_SECOND_PARAM) >> 4) & 0x3;
		}
		else
		{
			tparam = ((tparams & T_THIRD_PARAM) >> 2) & 0x3;
		}
		if (tparam == T_REG)
		{
			reg_number = as_byte(pc->vm_memory)[pc->ip];
			if (reg_number >= REG_NUMBER)
			{
				pc->alive = 0;
				return (param);
			}
			pc->ip += 1;
			memory_init(&param, &pc->reg[reg_number], REG_SIZE);
		}
		else if (tparam == T_DIR)
		{
			if (op_tab[opcode].tdir_size == 0)
			{
				memory_init(&param,  &pc->vm_memory[swap32((uint32_t*)&pc->vm_memory[pc->ip])], DIR_SIZE);
				pc->ip += DIR_SIZE;
			}
			else
			{
				memory_init(&param,  &pc->vm_memory[swap16((uint16_t*)&pc->vm_memory[pc->ip])], IND_SIZE);
				pc->ip += IND_SIZE;
			}
		}
		else if (tparam == T_IND)
		{
			//shrink by IDX_MOD?
			//param = (uint32_t*)&as_byte(pc->vm_memory)[pc->ip + *(int16_t*)&pc->vm_memory[pc->ip]];
			memory_init(&param, &as_byte(pc->vm_memory)[(pc->ip + *(int16_t*)&pc->vm_memory[pc->ip]) % MEM_SIZE], IND_SIZE); //not exactly
			pc->ip += IND_SIZE;
		}
		else
		{
			pc->alive = 0;
			return (param);
		}
	}
	return (param);
}

t_decoded_op	op_decode(struct s_thread *pc)
{
	t_decoded_op op;
	uint8_t tparams;

	op.opcode = decode_opcode(pc) - 1;
	if (pc->alive == 0)
	{
		return (op);
	}
	tparams = decode_tparams(pc, op.opcode);
	op.args[0] = decode_param(op.opcode, tparams, pc, 1);
	op.args[1] = decode_param(op.opcode, tparams, pc, 2);
	op.args[2] = decode_param(op.opcode, tparams, pc, 3);
	return (op);
}

void	op_exec(struct s_thread *pc)
{
	if (pc->op.opcode == no_op)
	{
		pc->op = op_decode(pc);
		pc->wait = op_tab[pc->op.opcode].cycle;
	}
	if (pc->wait)
	{
		return ;
	}
	if (pc->alive == 0)
	{
		return ;
	}
	opcalls[pc->op.opcode].opfunc(pc, &pc->op.args[0], &pc->op.args[1], &pc->op.args[2]);
	pc->op.opcode = no_op;
}

t_vm *get_vm(t_vm *vm)
{
	static t_vm *m_vm = 0;

	if (m_vm == 0)
	{
		m_vm = vm;
	}
	return (m_vm);
}

t_op    op_tab[17] =
				{
						{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
						{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
						{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
						{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
						{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
						{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
								"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
						{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
								"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
						{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
								"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
						{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
						{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
								"load index", 1, 1},
						{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
								"store index", 1, 1},
						{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
						{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
						{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
								"long load index", 1, 1},
						{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
						{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
						{0, 0, {0}, 0, 0, 0, 0, 0}
				};