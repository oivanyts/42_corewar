/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcalls3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:56:02 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 19:56:04 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opcalls.h"
#include "vm.h"
#include "vs.h"

void	f_sub(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
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
	sum = swap32(swap32(memory_tou32(p1)) - swap32(memory_tou32(p2)));
	memory_init_number(&res_memory, &sum);
	memory_memmove(p3, &res_memory);
	sp->cf = memory_iszero(p3);
}

void	f_and(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	if (!get_vm(0)->options.visual_ncurses && get_vm(0)->options.o_v_param & 4)
		output_operation(sp);
	if (((t_player*)(sp->player))->number == 1)
	{
		get_vm(0);
	}
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	memory_and(p3, p1, p2);
	sp->cf = memory_iszero(p3);
}

void	f_or(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	if (!get_vm(0)->options.visual_ncurses && get_vm(0)->options.o_v_param & 4)
		output_operation(sp);
	if (((t_player*)(sp->player))->number == 1)
	{
		get_vm(0);
	}
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	memory_or(p3, p1, p2);
	sp->cf = memory_iszero(p3);
}

void	f_xor(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	if (!get_vm(0)->options.visual_ncurses && get_vm(0)->options.o_v_param & 4)
		output_operation(sp);
	if (((t_player*)(sp->player))->number == 1)
	{
		get_vm(0);
	}
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	memory_xor(p3, p1, p2);
	sp->cf = memory_iszero(p3);
}

void	f_zjmp(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)p2;
	(void)p3;
	if (sp->cf)
	{
		load_dir_idx_param(sp, p1);
		sp->ip = (uint8_t*)p1->memory - sp->vm_memory;
	}
	if (get_vm(0)->options.visual_ncurses == 0
		&& get_vm(0)->options.o_v_param & 4)
	{
		output_operation(sp);
		if (sp->cf)
			ft_printf(" OK\n");
		else
			ft_printf(" FAILED\n");
	}
}
