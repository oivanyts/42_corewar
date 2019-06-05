/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcalls4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:21:44 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:21:45 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opcalls.h"
#include "vm.h"
#include "vs.h"

void	f_ldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	t_memory	mem;
	int32_t		up1;
	int32_t		up2;

	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	if (get_param_type(sp->op.opcode, sp->op.tparams, 1) == T_REG)
		up1 = swap32(memory_tou32(p1));
	else
		up1 = (int16_t)swap16(memory_tou16(p1));
	if (get_param_type(sp->op.opcode, sp->op.tparams, 2) == T_REG)
		up2 = swap32(memory_tou32(p2));
	else
		up2 = (int16_t)swap16(memory_tou16(p2));
	memory_init(&mem,
	&sp->vm_memory[(sp->op.ip + (up1 + up2) % IDX_MOD) % MEM_SIZE], REG_SIZE);
	memory_set_bounds(&mem, sp->vm_memory, sp->vm_memory + MEM_SIZE);
	memory_memmove(p3, &mem);
}

void	f_sti(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	t_memory	mem;
	int32_t		up2;
	int32_t		up3;

	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	if (get_param_type(sp->op.opcode, sp->op.tparams, 2) == T_REG)
		up2 = swap32(memory_tou32(p2));
	else
		up2 = (int16_t)swap16(memory_tou16(p2));
	if (get_param_type(sp->op.opcode, sp->op.tparams, 3) == T_REG)
		up3 = swap32(memory_tou32(p3));
	else
		up3 = (int16_t)swap16(memory_tou16(p3));
	memory_init(&mem, &sp->vm_memory[(sp->op.ip + (up2 + up3) % IDX_MOD)
		% MEM_SIZE], DIR_SIZE);
	memory_set_bounds(&mem, sp->vm_memory, sp->vm_memory + MEM_SIZE);
	memory_memmove(&mem, p1);
	get_vm(0)->options.visual_ncurses ? ft_changememvs((sp->op.ip + (up2 + up3)
		% IDX_MOD) % MEM_SIZE, ((t_player *)sp->player)->number) : 0;
}
