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

uint32_t	get_thread_number(const t_thread *pc)
{
	uint32_t	pc_i;

	pc_i = pc - threads_at(&get_vm(0)->threads, 0);
	return (pc_i);
}

void		op_start_processing(t_thread *pc)
{
	ft_memset(&pc->op, 0, sizeof(t_decoded_op));
	pc->op.valid = 1;
	pc->op.ip = pc->ip;
	pc->op.opcode = as_byte(pc->vm_memory)[pc->ip];
	if (pc->op.opcode < 1 || pc->op.opcode > 16)
	{
		pc->op.valid = 0;
		pc->wait = 1;
	}
	else
	{
		pc->wait = g_op_tab[pc->op.opcode - 1].cycle;
	}
	pc->op.opcode -= 1;
	pc->processing = 1;
}

void		op_exec(t_thread *pc)
{
	int pc_i;

	if (pc->processing == 0)
	{
		op_start_processing(pc);
	}
	if (pc->wait)
	{
		pc->wait -= 1;
		if (pc->wait)
			return ;
	}
	if (pc->alive == 0)
		return ;
	decode_opcode(pc);
	op_decode(pc);
	pc->processing = 0;
	pc_i = get_thread_number(pc);
	if (pc->op.valid)
	{
		g_opcalls[pc->op.opcode].opfunc(pc, &pc->op.args[0],
				&pc->op.args[1], &pc->op.args[2]);
	}
	!get_vm(0)->options.visual_ncurses && get_vm(0)->options.o_v_param & 16
		? print_moves(threads_at(&get_vm(0)->threads, pc_i)) : 0;
}

t_vm		*get_vm(t_vm *vm)
{
	static t_vm *m_vm = 0;

	if (m_vm == 0)
	{
		m_vm = vm;
	}
	return (m_vm);
}
