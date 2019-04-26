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

void	vm_cycle()
{

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

uint32_t	*decode_param(t_opcode opcode, uint8_t tparams, t_carriage *pc, uint8_t param_number)
{
	uint32_t *param;
	uint8_t  tparam;
	uint8_t reg_number;

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

		}
		else if (tparam == T_IND)
		{

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

void	op_exec(struct s_decoded_op *data)
{

}

inline uint8_t	*as_byte(void *ptr)
{
	return (ptr);
}