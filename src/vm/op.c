/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:57:21 by myaremen          #+#    #+#             */
/*   Updated: 2019/04/25 15:57:23 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void *vm_memory;

void	players_sort_by_id(t_player *players, uint32_t nplayers)
{

}

bool anybody_alive(t_player *players, uint32_t nplayers)
{
	uint32_t player;
	bool alive;

	player = 0;
	alive = 0;
	while (player < nplayers)
	{
		if (players[player].carriage.alive)
		{
			alive = 1;
		}
		++player;
	}
	return (alive);
}

void	vm_cycle(t_player *players, uint32_t nplayers)
{
	uint32_t player;
	uint32_t cycles;
	uint32_t checks;

	cycles = CYCLE_TO_DIE;
	player = 0;
	checks = 0;
	while (anybody_alive(players, nplayers) && (cycles > 0))
	{
		++checks;
		if (checks == MAX_CHECKS)
		{
			cycles -= CYCLE_DELTA;
		}
		op_exec(&players[player].carriage);
		++player;
		if (player == nplayers)
		{
			player = 0;
		}
	}
}

t_opcode decode_opcode(struct s_carriage *pc)
{
	t_opcode opcode;

	if (pc->ip == MEM_SIZE)
	{
		pc->ip = 0;
	}
	opcode = as_byte(vm_memory)[pc->ip];
	if (opcode <= oplowborder || opcode >= ophighborder)
	{
		pc->alive = 0;
		return (opcode);
	}
	pc->ip += 1;
	return (opcode);
}

void	check_op_params(t_opcode opcode, uint8_t tparams)
{
	if ((t_ops[opcode].targs[0] & (tparams & T_FIRST_PARAM)) == 0)
	{
		//error
	}
	else if ((t_ops[opcode].targs[1] & (tparams & T_SECOND_PARAM)) == 0)
	{
		//error
	}
	else if ((t_ops[opcode].targs[0] & (tparams & T_FIRST_PARAM)) == 0)
	{
		//error
	}
}

uint8_t	decode_tparams(struct s_carriage *pc, t_opcode opcode)
{
	uint8_t tparams;

	if (t_ops[opcode].nargs > 0 && pc->ip == MEM_SIZE)
	{
		//error
	}
	tparams = as_byte(vm_memory)[pc->ip];
	check_op_params(opcode, tparams);
	pc->ip += 1;
	return (tparams);
}

void	*decode_param(t_opcode opcode, uint8_t tparams, t_carriage *pc, uint8_t param_number)
{
	void *param;
	uint8_t  tparam;
	uint8_t reg_number;
	uint32_t addr;

	param = 0;
	if (param_number <= t_ops[opcode].nargs)
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
			reg_number = as_byte(vm_memory)[pc->ip];
			if (reg_number == 0 || reg_number > REG_NUMBER)
			{
				//error
			}
			param = &pc->reg[reg_number - 1];
		}
		else if (tparam == T_DIR)
		{
			param = (uint32_t*)as_byte(vm_memory)[pc->ip];

		}
		else if (tparam == T_IND)
		{
			addr = pc->ip + as_byte(vm_memory)[pc->ip];
			addr = pc->ip % MEM_SIZE;
			param = (uint32_t*)&as_byte(vm_memory)[addr];
			pc->ip += 2;
		}
		else
		{
			//error
		}
	}
	return (param);
}

t_decoded_op	op_decode(struct s_carriage *pc)
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

void	op_exec(struct s_carriage *pc)
{
	t_decoded_op op;

	op = op_decode(pc);
	t_ops[op.opcode].op(op.args[0], op.args[1], op.args[2]);
}

inline uint8_t	*as_byte(void *ptr)
{
	return (ptr);
}