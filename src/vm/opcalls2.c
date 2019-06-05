/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcalls2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:55:56 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 19:55:57 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opcalls.h"
#include "vm.h"
#include "vs.h"

void	load_idx_param(t_thread *sp, t_memory *mem, uint8_t param_number)
{

	if (get_param_type(sp->op.opcode, sp->op.tparams, param_number) == T_DIR)
	{
		load_dir_idx_param(sp, mem);
	}
	else if (get_param_type(sp->op.opcode, sp->op.tparams, param_number)
		== T_IND)
	{
		load_ind_param(sp, mem);
	}
	else
	{
		handle_error(error_wrong_tparam);
	}
}

void	f_live(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	static int count = 0;
	int32_t p32;

	if (!get_vm(0)->options.visual_ncurses && get_vm(0)->options.o_v_param & 4)
		output_operation(sp);
	p2 = p3;
	if (get_vm(0)->cycle >= 17704)
	{
		get_vm(0);
		++count;
		get_vm(0);
	}
	sp->lives += 1;
	sp->last_live = get_vm(0)->cycle;
	load_param(sp, p1, 1);
	p32 = memory_tou32(p1);
	p32 = swap32(p32);
	if (-p32 > 0 && -p32 <= get_vm(0)->nplayers)
	{
		if (!get_vm(0)->options.visual_ncurses
			&& get_vm(0)->options.o_v_param & 1)
			ft_printf("Player %d (%s) is said to be alive\n",
					get_vm(0)->players[-p32 - 1].number,
					get_vm(0)->players[-p32 - 1].header.prog_name);
		get_vm(0)->last_alive = -p32;
		if (get_vm(0)->options.visual_ncurses)
			ft_initlive(sp, p32);
	}
}

void	f_ld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)p3;
	if (!get_vm(0)->options.visual_ncurses && get_vm(0)->options.o_v_param & 4)
		output_operation(sp);
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	memory_memmove(p2, p1);
	sp->cf = memory_iszero(p2);
//	if (get_vm(0)->options.visual_ncurses == 0
//		&& get_vm(0)->options.o_v_param & 4)
//	{
//		ft_printf("P    %d | %s %d r%d\n", sp - threads_at(&get_vm(0)->threads,
//			0) + 1, g_op_tab[sp->op.opcode].name, swap32(memory_tou32(p1)),
//				(uint32_t *)p2->memory - (uint32_t *)&sp->reg[0] + 1);
//	}
}

void	f_st(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;
	(void)p3;
	if (!get_vm(0)->options.visual_ncurses && get_vm(0)->options.o_v_param & 4)
		output_operation(sp);
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	memory_memmove(p2, p1);
	if (get_param_type(sp->op.opcode, sp->op.tparams, 2)
		== T_IND && get_vm(0)->options.visual_ncurses)
		ft_changememvs(((uint8_t *)p2->memory - &sp->vm_memory[0]),
					((t_player *)sp->player)->number);
}

void	f_add(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	uint32_t sum;
	t_memory res_memory;

	if (!get_vm(0)->options.visual_ncurses && get_vm(0)->options.o_v_param & 4)
		output_operation(sp);
	if (((t_player*)(sp->player))->number == 1)
	{
		get_vm(0);
	}
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	sum = swap32(swap32(memory_tou32(p1)) + swap32(memory_tou32(p2)));
	memory_init_number(&res_memory, &sum);
	memory_memmove(p3, &res_memory);
	sp->cf = memory_iszero(p3);
}
