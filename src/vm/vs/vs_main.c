/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 12:44:52 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/27 12:46:07 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "asm.h"
#include "vm.h"
#include "vs.h"

#define NLINES 10
#define NCOLS 40

void	ft_initcolors(void)
{
	init_color(COLOR_GRAY, 455, 455, 455);
	init_pair(BORDER_GRAY, COLOR_GRAY, COLOR_GRAY);
	init_pair(GRAY, COLOR_GRAY, 0);
	init_pair(RED, COLOR_RED, 0);
	init_pair(GREEN, COLOR_GREEN, 0);
	init_pair(YELLOW, COLOR_YELLOW, 0);
	init_pair(BLUE, COLOR_BLUE, 0);
}

void	ft_drawmap(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		wattron(g_vs->mem_win, COLOR_PAIR(g_vsmap[i].player + 10));
		mvwprintw(g_vs->mem_win, i / 64 + 2, (i % 64) * 3 + 3, "%.2x", (threads_at(&vm->threads, 0))->vm_memory[i]);
//		mvwprintw(g_vs->mem_win, i / 64 + 2, (i % 64) * 3 + 3, "%.2d", g_vsmap[i].player);
		wattroff(g_vs->mem_win, COLOR_PAIR(g_vsmap[i].player + 10));
		i++;
	}
	mvwprintw(g_vs->info_win, 3, 3, "Cycle : %-3d", vm->cycle);
	wrefresh(g_vs->mem_win);
	wrefresh(g_vs->info_win);
//	getch();
//	endwin();

}

void	ft_initvsmap(int playern, t_player *player, t_vm *vm)
{
	int i;
	int imax;

	i = playern * MEM_SIZE / vm->nplayers;
	imax = i + player[playern].header.prog_size;
	while (i < imax)
	{
		(g_vsmap[i]).player = player[playern].number;
		i++;
	}

}

void ft_vsinit()
{
	chtype ch;

	initscr();
//	cbreak();
//	noecho();
//	keypad(stdscr, TRUE);
	curs_set(0);
	if (!has_colors())
	{
		endwin();
		ft_printf("\nОшибка! Не поддерживаются цвета\n");
		return ;
	}
	g_vs = (t_vs *)ft_memalloc(sizeof(t_vs));
	g_vsmap = (t_vsmap *)ft_memalloc(sizeof(t_vsmap) * MEM_SIZE);
	start_color();
	ft_initcolors();
	refresh();
	g_vs->mem_win = newwin(68, 197, 0, 0);
	g_vs->info_win = newwin(68, 58, 0, 196);
	ch = '+' | COLOR_PAIR(BORDER_GRAY);
	wborder(g_vs->mem_win, ch, ch, ch, ch, ch, ch, ch, ch);
	wborder(g_vs->info_win, ch, ch, ch, ch, ch, ch, ch, ch);
	mvwprintw(g_vs->info_win, 3, 3, "%d", COLOR_BLUE);
	wrefresh(g_vs->mem_win);
	wrefresh(g_vs->info_win);
//	refresh();
//	getch();
//	endwin();
}
