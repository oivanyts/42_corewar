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
		if (threads_pat(&player->threads, thread)->alive)
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
			func(threads_pat(&players[player].threads, player_thread));
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
	if (opcode <= oplowborder || opcode >= ophighborder)
	{
		pc->alive = 0;
		return (opcode);
	}
	pc->ip += 1;
	return (opcode);
}

bool	check_op_params(t_opcode opcode, uint8_t tparams)
{
	if ((op_tab[opcode].targs[0] & (tparams & T_FIRST_PARAM)) == 0)
	{
		return (0);
	}
	else if ((op_tab[opcode].targs[1] & (tparams & T_SECOND_PARAM)) == 0)
	{
		return (0);
	}
	else if ((op_tab[opcode].targs[0] & (tparams & T_FIRST_PARAM)) == 0)
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

	tparams = (1 << 7);
	if (op_tab[opcode].codoctal == 1)
	{
		tparams = as_byte(pc->vm_memory)[pc->ip % MEM_SIZE];
		if (!check_op_params(opcode, tparams))
		{
			pc->alive = 0;
			return (tparams);
		}
		pc->ip += 1;
	}
	return (tparams);
}

void	*decode_param(t_opcode opcode, uint8_t tparams, t_thread *pc, uint8_t param_number)
{
	void *param;
	uint8_t  tparam;
	uint8_t reg_number;

	param = 0;
	if (param_number <= op_tab[opcode].args)
	{
		if (param_number == 1)
		{
			tparam = tparams & T_FIRST_PARAM;
		}
		else if (param_number == 2)
		{
			tparam = tparams & T_SECOND_PARAM;
		}
		else
		{
			tparam = tparams & T_THIRD_PARAM;
		}
		if (tparam == T_REG)
		{
			reg_number = as_byte(pc->vm_memory)[pc->ip];
			if (reg_number >= REG_NUMBER)
			{
				pc->alive = 0;
				return (0);
			}
			param = &pc->reg[reg_number];
		}
		else if (tparam == T_DIR)
		{
			param = &pc->vm_memory[pc->ip];
			if (op_tab[opcode].tdir_size == 0)
			{
				pc->ip += 4;
			}
			else
			{
				pc->ip += 2;
			}
		}
		else if (tparam == T_IND)
		{
			//shrink IND address
			param = (uint32_t*)&as_byte(pc->vm_memory)[pc->ip + *(int16_t*)&pc->vm_memory[pc->ip]];
			pc->ip += 2;
		}
		else
		{
			pc->alive = 0;
			return (0);
		}
	}
	return (param);
}

t_decoded_op	op_decode(struct s_thread *pc)
{
	t_decoded_op op;
	uint8_t tparams;

	op.opcode = decode_opcode(pc);
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
	t_decoded_op op;

	if (pc->wait)
	{
		return ;
	}
	op = op_decode(pc);
	opcalls[op.opcode].opfunc(pc, op.args[0], op.args[1], op.args[2]);
}

uint8_t	*as_byte(void *ptr)
{
	return (ptr);
}