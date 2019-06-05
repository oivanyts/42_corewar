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

void		output_operation(t_thread *sp)
{
	uint8_t		i;
	uint8_t		arg_type;

	i = 0;
	ft_printf("P    %d | %s", sp - threads_at(&get_vm(0)->threads, 0) + 1,
			g_op_tab[sp->op.opcode].name);
	while (i < g_op_tab[sp->op.opcode].args)
	{
		if ((arg_type = get_param_type(sp->op.opcode, sp->op.tparams, i + 1)) == T_REG)
		{
			ft_printf(" r%d", (memory_tou8(&sp->op.args[i])));
		}
		else
		{
			if (arg_type == T_IND || g_op_tab[sp->op.opcode].tdir_size)
				ft_printf(" %d", (int16_t)swap16(memory_tou16(&sp->op.args[i])));
			else
				ft_printf(" %d", (int16_t)swap32(memory_tou32(&sp->op.args[i])));
		}
		i++;
	}
	if (sp->op.opcode != 8)
		ft_printf("\n");
}


void	f_ldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	t_memory	mem;
	int32_t		up1;
	int32_t		up2;

	if (!get_vm(0)->options.visual_ncurses && get_vm(0)->options.o_v_param & 4)
		output_operation(sp);
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
	if (!get_vm(0)->options.visual_ncurses && get_vm(0)->options.o_v_param & 4)
	{
		output_operation(sp);
		ft_printf("\t   | -> store to %d + %d = %d (with pc and mod %d)\n", up2,
				  up3, up2 + up3, (sp->op.ip + (up2 + up3) % IDX_MOD) % MEM_SIZE);
	}
	get_vm(0)->options.visual_ncurses ? ft_changememvs((sp->op.ip + (up2 + up3)
		% IDX_MOD) % MEM_SIZE, ((t_player *)sp->player)->number) : 0;
}
