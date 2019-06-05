/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:44:49 by npiatiko          #+#    #+#             */
/*   Updated: 2019/06/04 16:44:50 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vs.h"

void	ft_drawcarriage(t_thread *th)
{
	if (th->alive && !(g_vsmap[th->ip].live))
	{
		wattrset(g_vs->mem_win,
				COLOR_PAIR(g_vsmap[th->ip].player + 10) | A_REVERSE);
		mvwprintw(g_vs->mem_win, th->ip / 64 + 2, (th->ip % 64) * 3 + 3,
				"%.2x", th->vm_memory[th->ip]);
	}
}

int		ft_getattr(int i)
{
	int	color;

	color = COLOR_PAIR(g_vsmap[i].player + 10);
	if (g_vsmap[i].live > 0)
	{
		g_vsmap[i].live--;
		color = COLOR_PAIR(g_vsmap[i].liveplayer + 20) | A_BOLD;
	}
	else if (g_vsmap[i].newdata > 0)
	{
		g_vsmap[i].newdata--;
		color = color | A_BOLD;
	}
	else if (!g_vsmap[i].player)
		color = color | A_BOLD;
	return (color);
}

void	ft_drawmap(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		wattrset(g_vs->mem_win, ft_getattr(i));
		mvwprintw(g_vs->mem_win, i / 64 + 2, (i % 64) * 3 + 3, "%.2x",
				(threads_at(&vm->threads, 0))->vm_memory[i]);
		i++;
	}
	foreach_thread(&vm->threads, ft_drawcarriage);
	wrefresh(g_vs->mem_win);
	ft_kbhandler(vm);
}
