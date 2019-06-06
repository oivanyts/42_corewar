/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_fns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:18:04 by npiatiko          #+#    #+#             */
/*   Updated: 2019/06/04 16:18:05 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vs.h"

void	ft_announcewinner(int32_t number, char *name)
{
	wattron(g_vs->info_win, COLOR_PAIR(WHITE) | A_BOLD);
	mvwprintw(g_vs->info_win, 41, 3, "The winner is : ");
	wattron(g_vs->info_win, COLOR_PAIR(number + 10) | A_BOLD);
	wprintw(g_vs->info_win, name);
	nodelay(stdscr, FALSE);
	wattron(g_vs->info_win, COLOR_PAIR(WHITE) | A_BOLD | A_BLINK);
	mvwprintw(g_vs->info_win, 43, 3, "Press any key to exit.");
	wrefresh(g_vs->info_win);
	getch();
	ft_vsexit();
}

void	ft_vsexit(void)
{
	endwin();
	free(g_vs);
	free(g_vsmap);
}

int		ft_getnchars(int lives)
{
	float j;

	j = (((float)lives / (float)g_vs->sumlives) * (float)50);
	return ((int)(j - (int)j >= 1.0 / (float)get_vm(0)->nplayers ? j + 1 : j));
}

void	ft_resetlivesinper(t_vm *vm)
{
	int	i;

	if (vm->options.visual_ncurses)
	{
		ft_printlivebar(get_vm(0), 3);
		i = vm->nplayers;
		while (i--)
			vm->players[i].livesinper = 0;
		g_vs->sumlives = 0;
	}
}

void	ft_changememvs(int memstart, int player)
{
	int	i;

	i = 4;
	while (i--)
	{
		g_vsmap[memstart % MEM_SIZE].player = player;
		g_vsmap[memstart % MEM_SIZE].newdata = 50;
		memstart++;
	}
}
