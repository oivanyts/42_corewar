/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:11:10 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:11:11 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		decode_reg_param(t_thread *pc, t_memory *param)
{
	if (as_byte(pc->vm_memory)[pc->ip] > REG_NUMBER
		|| as_byte(pc->vm_memory)[pc->ip] == 0)
	{
		pc->op.valid = 0;
	}
	memory_init(param, &(pc->vm_memory)[pc->ip], T_REG);
	memory_set_bounds(param, param->memory, param->memory + 8);
	pc->ip += 1;
}

void		decode_dir_param(t_thread *pc, t_memory *param, t_decoded_op op)
{
	if (g_op_tab[op.opcode].tdir_size == 0)
	{
		memory_init(param, &pc->vm_memory[pc->ip], DIR_SIZE);
		pc->ip += DIR_SIZE;
	}
	else
	{
		memory_init(param, &pc->vm_memory[pc->ip], IND_SIZE);
		pc->ip += IND_SIZE;
	}
	memory_set_bounds(param, pc->vm_memory, pc->vm_memory + MEM_SIZE);
}

void		decode_ind_param(t_thread *pc, t_memory *param)
{
	memory_init(param, &pc->vm_memory[pc->ip], IND_SIZE);
	memory_set_bounds(param, pc->vm_memory, pc->vm_memory + MEM_SIZE);
	pc->ip += IND_SIZE;
}

t_memory	decode_param(t_decoded_op op, t_thread *pc, uint8_t param_number)
{
	t_memory	param;
	uint8_t		tparam;

	memory_init(&param, 0, 0);
	if (param_number <= g_op_tab[op.opcode].args)
	{
		tparam = force_get_param_type(pc->op.tparams, param_number);
		if (tparam == T_REG)
			decode_reg_param(pc, &param);
		else if (tparam == T_DIR)
			decode_dir_param(pc, &param, op);
		else if (tparam == T_IND)
			decode_ind_param(pc, &param);
		else
			pc->op.valid = 0;
		pc->ip %= MEM_SIZE;
	}
	return (param);
}
