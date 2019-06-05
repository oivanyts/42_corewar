/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:16:37 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:16:38 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_moves(const t_thread *pc)
{
	int8_t	i;
	int8_t	funcsize;

	i = 0;
	if ((pc->op.opcode == 8 && pc->cf)
		|| (pc->op.opcode < 0 || pc->op.opcode > 15))
	{
		return ;
	}
	else
	{
		funcsize = pc->ip % MEM_SIZE - pc->op.ip % MEM_SIZE;
	}
	ft_printf("ADV %d (0x%0.4x -> 0x%0.4x)",
			funcsize, pc->op.ip % MEM_SIZE, pc->ip % MEM_SIZE);
	while (i < funcsize)
	{
		ft_printf(" %0.2x", (uint8_t)pc->vm_memory[(pc->op.ip + i) % MEM_SIZE]);
		i++;
	}
	ft_printf(" \n", g_op_tab[pc->op.opcode].name);
}
