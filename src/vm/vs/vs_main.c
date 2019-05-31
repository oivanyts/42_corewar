/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 12:44:52 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/30 17:04:02 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "asm.h"
#include "vm.h"
#include "vs.h"
#include <sys/time.h>

#define NLINES 10
#define NCOLS 40

int		ft_getnchars(int lives)
{
	float j;

	j = (((float)lives / (float)g_vs->sumlives) * (float)50);
	return ((int)(j - (int)j >= 1.0 / (float)get_vm(0)->nplayers ? j + 1 : j));
}

void	ft_resetlivesinper(t_vm *vm)
{
	int 	i;

	ft_printlivebar(get_vm(0), 3);
	i = vm->nplayers;
	while (i--)
		vm->players[i].livesinper = 0;
	g_vs->sumlives = 0;
}

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

void	ft_changememvs(int memstart, int player)
{
	int		i = 4;
	while (i--)
	{
		g_vsmap[memstart % 4095].player = player;
		g_vsmap[memstart % 4095].newdata = 50;
		memstart++;
	}
}

int 	ft_getattr(int i)
{
	if (g_vsmap[i].newdata > 0)
	{
		g_vsmap[i].newdata--;
		return (A_BOLD);
	}
	else if (!g_vsmap[i].player)
		return (A_BOLD);
	return (0);
}

void	ft_drawlive(int i)
{
	if (g_vsmap[i].live > 0)
	{
		g_vsmap[i].live--;
		wattrset(g_vs->mem_win, COLOR_PAIR(g_vsmap[i].liveplayer + 20) | A_BOLD);
		if (g_vsmap[i].liveplayer > 4 || g_vsmap[i].liveplayer < 1)
			mvwprintw(g_vs->info_win, 8, 3, "player : %08d", g_vsmap[i].liveplayer);
	}
}

void ft_speedcontroll()
{
	static long long int	prevtime = 0;
	struct timeval			curtime;
	long long int 			dusec;

	wattron(g_vs->info_win, COLOR_PAIR(WHITE));
	gettimeofday(&curtime, NULL);
	dusec = (curtime.tv_sec * SEC + curtime.tv_usec) - prevtime;
	if (dusec < SEC / g_vs->speed)
	{
		usleep(SEC / g_vs->speed - dusec);
		curtime.tv_usec += SEC / g_vs->speed - dusec;
	}
	prevtime = curtime.tv_sec * SEC + curtime.tv_usec;
}

void	ft_printlivebar(t_vm *vm, int indent)
{
	int i;

	i = vm->nplayers;
	wattrset(g_vs->info_win, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(g_vs->info_win, 28 + indent, 3, "[--------------------------------------------------]");
	wmove(g_vs->info_win, 28 + indent, 4);
	while (i-- && g_vs->sumlives)
	{
		wattrset(g_vs->info_win, COLOR_PAIR(vm->players[i].number + 10) | A_BOLD);
		wprintw(g_vs->info_win,"%.*s",ft_getnchars(vm->players[i].livesinper) , "--------------------------------------------------");
	}
	wattrset(g_vs->info_win, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(g_vs->info_win, 28 + indent, 54, "]");
}

void	ft_printinfo(t_vm *vm, int delay, int key)
{
	int i;

	wattrset(g_vs->info_win, COLOR_PAIR(WHITE) | A_BOLD);
	mvwprintw(g_vs->info_win, 27, 3, "Live breakdown for current period :");
	mvwprintw(g_vs->info_win, 30, 3, "Live breakdown for last period :");
	mvwprintw(g_vs->info_win, 7, 3, "Cycle : %-3d", vm->cycle * (bool) vm->last_alive);
	mvwprintw(g_vs->info_win, 5, 3, "key  : %c", key);
	mvwprintw(g_vs->info_win, 2, 3, "%-13s", delay ? "** RUNNING ** " : "** PAUSED **");
	mvwprintw(g_vs->info_win, 4, 3, "Cycles/second limit : %-5d", g_vs->speed);
	i = vm->nplayers;
	while (i--)
	{
		wattrset(g_vs->info_win, COLOR_PAIR(WHITE));
		mvwprintw(g_vs->info_win, 23 - (vm->nplayers - 1 - i) * 4 + 1, 3, "Last live :%22d", vm->players[i].lastlive);
		mvwprintw(g_vs->info_win, 23 - (vm->nplayers - 1 - i) * 4 + 2, 3, "Lives in current period :%8d",
				  vm->players[i].livesinper);
		mvwprintw(g_vs->info_win, 23 - (vm->nplayers - 1 - i) * 4, 3, "Player -%d : ", vm->players[i].number);
		wattrset(g_vs->info_win, COLOR_PAIR(vm->players[i].number + 10) | A_BOLD);
		wprintw(g_vs->info_win, "%.41s", vm->players[i].header.prog_name);
	}
	ft_printlivebar(vm, 0);
	wrefresh(g_vs->info_win);
}

void	ft_kbhandler(t_vm *vm)
{
	static int	delay = 0;
	static int	key = -1;

	ft_speedcontroll();
	while (true)
	{
		if (key == ' ')
			delay = !delay;
		else if (key == '=')
			g_vs->speed == INT_MAX ? 0 : ++g_vs->speed;
		else if (key == '-')
			g_vs->speed == 1 ? 0 : g_vs->speed--;
		else if (key == '+')
			g_vs->speed += 10;
		else if (key == '_')
			g_vs->speed = g_vs->speed < 11 ? g_vs->speed : g_vs->speed - 10;
		nodelay(stdscr, delay);
		ft_printinfo(vm, delay, key);
		key = getch();
		if (delay || (!ft_strchr("-_=+ ", key) && key > 0))
			break;
	}
}

void	ft_drawcarriage(t_thread *th)
{
	if (th->alive && !(g_vsmap[th->ip].live))
	{
		wattrset(g_vs->mem_win, COLOR_PAIR(g_vsmap[th->ip].player + 10) | A_REVERSE);
		mvwprintw(g_vs->mem_win, th->ip / 64 + 2, (th->ip % 64) * 3 + 3, "%.2x", th->vm_memory[th->ip]);
	}
}
void	ft_drawmap(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		wattrset(g_vs->mem_win, COLOR_PAIR(g_vsmap[i].player + 10) | ft_getattr(i));
		ft_drawlive(i);
		mvwprintw(g_vs->mem_win, i / 64 + 2, (i % 64) * 3 + 3, "%.2x", (threads_at(&vm->threads, 0))->vm_memory[i]);
//		mvwprintw(g_vs->mem_win, i / 64 + 2, (i % 64) * 3 + 3, "%.2d", g_vsmap[i].player);
//		wattroff(g_vs->mem_win, COLOR_PAIR(g_vsmap[i].player + 10));
		i++;
	}
	foreach_thread(&vm->threads, ft_drawcarriage);
//	wattrset(g_vs->info_win, COLOR_PAIR(WHITE));
//	mvwprintw(g_vs->info_win, 7, 3, "Cycle : %-3d", vm->cycle);
//	mvwprintw(g_vs->info_win, 6, 3, "Cycle : %08d", COLOR_PAIR(11));
//	mvwprintw(g_vs->info_win, 7, 3, "Cycle : %08d", COLOR_PAIR(222));

	wrefresh(g_vs->mem_win);
//	wrefresh(g_vs->info_win);
	ft_kbhandler(vm);
//	getch();
//	endwin();

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

void ft_vsinit(t_vm *vm, t_player *players)
{
	chtype ch;

	initscr();
	noecho();
//	keypad(stdscr, TRUE);
//	nodelay(stdscr, FALSE);
//	cbreak();
	curs_set(0);
	if (!has_colors())
	{
		endwin();
		ft_printf("\nОшибка! Не поддерживаются цвета\n");
		return ;
	}
	g_vs = (t_vs *)ft_memalloc(sizeof(t_vs));
	g_vsmap = (t_vsmap *)ft_memalloc(sizeof(t_vsmap) * MEM_SIZE);
	ft_initvsmap(vm, players);
	start_color();
	ft_initcolors();
	refresh();
	g_vs->mem_win = newwin(68, 197, 0, 0);
	g_vs->info_win = newwin(68, 58, 0, 196);
	g_vs->speed = 50;
	ch = '+' | COLOR_PAIR(BORDER_GRAY);
	wborder(g_vs->mem_win, ch, ch, ch, ch, ch, ch, ch, ch);
	wborder(g_vs->info_win, ch, ch, ch, ch, ch, ch, ch, ch);
	wattron(g_vs->info_win, COLOR_PAIR(WHITE));
	mvwprintw(g_vs->info_win, 2, 3,"** PAUSED **");
//	mvwprintw(g_vs->info_win, 10, 3, "%d", getch());
	wrefresh(g_vs->mem_win);
	wrefresh(g_vs->info_win);
	ft_drawmap(vm);
//	refresh();
//	getch();
//	endwin();
}
