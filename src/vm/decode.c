/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:14:14 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:14:15 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		decode_opcode(struct s_thread *pc)
{
	pc->ip += 1;
	pc->ip %= MEM_SIZE;
}

bool		check_op_params(uint8_t opcode, uint8_t tparams)
{
	if (g_op_tab[opcode].targs[0] && get_param_type(opcode, tparams, 1) == 0)
	{
		return (0);
	}
	else if (g_op_tab[opcode].targs[1]
	&& get_param_type(opcode, tparams, 2) == 0)
	{
		return (0);
	}
	else if (g_op_tab[opcode].targs[2]
	&& get_param_type(opcode, tparams, 3) == 0)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

uint8_t		decode_tparams_manual(uint8_t opcode)
{
	uint8_t	tparams;

	tparams = 0;
	if (g_op_tab[opcode].targs[0] & T_REG)
		tparams |= (REG_CODE << 6);
	if (g_op_tab[opcode].targs[0] & T_DIR)
		tparams |= (DIR_CODE << 6);
	if (g_op_tab[opcode].targs[0] & T_IND)
		tparams |= (IND_CODE << 6);
	if (g_op_tab[opcode].targs[1] & T_REG)
		tparams |= (REG_CODE << 4);
	if (g_op_tab[opcode].targs[1] & T_DIR)
		tparams |= (DIR_CODE << 4);
	if (g_op_tab[opcode].targs[1] & T_IND)
		tparams |= (IND_CODE << 4);
	if (g_op_tab[opcode].targs[2] & T_REG)
		tparams |= (REG_CODE << 2);
	if (g_op_tab[opcode].targs[2] & T_DIR)
		tparams |= (DIR_CODE << 2);
	if (g_op_tab[opcode].targs[2] & T_IND)
		tparams |= (IND_CODE << 2);
	return (tparams);
}

uint8_t		decode_tparams(struct s_thread *pc, uint8_t opcode)
{
	uint8_t	tparams;

	tparams = 0;
	if (g_op_tab[opcode].codoctal)
	{
		tparams = as_byte(pc->vm_memory)[pc->ip];
		if (!check_op_params(opcode, tparams))
		{
			pc->op.valid = 0;
		}
		pc->ip += 1;
		pc->ip %= MEM_SIZE;
	}
	else
	{
		tparams = decode_tparams_manual(opcode);
	}
	return (tparams);
}

void		op_decode(t_thread *pc)
{
	if (pc->op.valid == 0)
	{
		return ;
	}
	pc->op.tparams = decode_tparams(pc, pc->op.opcode);
	pc->op.args[0] = decode_param(pc->op, pc, 1);
	pc->op.args[1] = decode_param(pc->op, pc, 2);
	pc->op.args[2] = decode_param(pc->op, pc, 3);
}
