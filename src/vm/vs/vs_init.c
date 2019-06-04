/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:44:34 by npiatiko          #+#    #+#             */
/*   Updated: 2019/06/04 16:44:34 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vs.h"

void	ft_initcolors(void)
{
	init_color(COLOR_GRAY, 455, 455, 455);
	init_pair(BORDER_GRAY, 8, 8);
	init_pair(GRAY, 8, 0);
	init_pair(RED, COLOR_RED, 0);
	init_pair(GREEN, COLOR_GREEN, 0);
	init_pair(CYAN, COLOR_CYAN, 0);
	init_pair(BLUE, COLOR_BLUE, 0);
	init_pair(LIVE_RED, 15, COLOR_RED);
	init_pair(LIVE_GREEN, 15, COLOR_GREEN);
	init_pair(LIVE_CYAN, 15, COLOR_CYAN);
	init_pair(LIVE_BLUE, 15, COLOR_BLUE);
	init_pair(WHITE, 15, 0);
}

void	ft_initvsmap(t_vm *vm, t_player *player)
{
	int i;
	int imax;
	int	playern;

	playern = 0;
	while (playern < vm->nplayers)
	{
		i = playern * MEM_SIZE / vm->nplayers;
		imax = i + player[playern].header.prog_size;
		while (i < imax)
		{
			(g_vsmap[i]).player = player[playern].number;
			i++;
		}
		playern++;
	}
}

void	ft_initscr(t_vm *vm, t_player *players)
{
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	if (!has_colors())
	{
		endwin();
		handle_error(error_colors);
	}
	g_vs = (t_vs *)ft_memalloc(sizeof(t_vs));
	g_vsmap = (t_vsmap *)ft_memalloc(sizeof(t_vsmap) * MEM_SIZE);
	if (!g_vs || !g_vsmap)
	{
		endwin();
		ft_vsexit();
		handle_error(error_memalloc);
	}
	ft_initvsmap(vm, players);
	start_color();
	ft_initcolors();
	refresh();
	g_vs->mem_win = newwin(68, 197, 0, 0);
	g_vs->info_win = newwin(68, 58, 0, 196);
}

void	ft_vsinit(t_vm *vm, t_player *players)
{
	chtype ch;

	ft_initscr(vm, players);
	g_vs->speed = 50;
	ch = '+' | COLOR_PAIR(BORDER_GRAY);
	wborder(g_vs->mem_win, ch, ch, ch, ch, ch, ch, ch, ch);
	wborder(g_vs->info_win, ch, ch, ch, ch, ch, ch, ch, ch);
	ft_printlivebar(vm, 3);
	ft_drawmap(vm);
}
