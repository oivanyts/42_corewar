/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:44:18 by npiatiko          #+#    #+#             */
/*   Updated: 2019/06/04 16:44:18 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vs.h"
#include <sys/time.h>
#include "error.h"

void	ft_printlivebar(t_vm *vm, int indent)
{
	int i;

	i = vm->nplayers;
	wattrset(g_vs->info_win, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(g_vs->info_win, 28 + indent, 3,
			"[--------------------------------------------------]");
	wmove(g_vs->info_win, 28 + indent, 4);
	while (i-- && g_vs->sumlives)
	{
		wattrset(g_vs->info_win, COLOR_PAIR(PLAYER_COLOR) | A_BOLD);
		wprintw(g_vs->info_win, "%.*s", ft_getnchars(vm->players[i].livesinper),
				"--------------------------------------------------");
	}
	wattrset(g_vs->info_win, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(g_vs->info_win, 28 + indent, 54, "]  ");
}

void	ft_printplayers(t_vm *vm)
{
	int		i;

	i = vm->nplayers;
	while (i--)
	{
		wattrset(g_vs->info_win, COLOR_PAIR(WHITE) | A_BOLD);
		mvwprintw(g_vs->info_win, 23 - (vm->nplayers - 1 - i) * 4 + 1, 3,
				"  Last live :%22d", vm->players[i].lastlive);
		mvwprintw(g_vs->info_win, 23 - (vm->nplayers - 1 - i) * 4 + 2, 3,
				"  Lives in current period :%8d", vm->players[i].livesinper);
		mvwprintw(g_vs->info_win, 23 - (vm->nplayers - 1 - i) * 4, 3,
				"Player -%d : ", vm->players[i].number);
		wattrset(g_vs->info_win, COLOR_PAIR(PLAYER_COLOR) | A_BOLD);
		wprintw(g_vs->info_win, "%.41s", vm->players[i].header.prog_name);
	}
}

void	ft_printinfo(t_vm *vm, int delay, int key)
{
	wattrset(g_vs->info_win, COLOR_PAIR(WHITE) | A_BOLD);
	mvwprintw(g_vs->info_win, 7, 3, "Cycle : %-3d",
			vm->cycle * (bool)vm->last_alive);
	mvwprintw(g_vs->info_win, 5, 3, "key  : %d", key);
	mvwprintw(g_vs->info_win, 2, 3, "%-13s",
			delay ? "** RUNNING ** " : "** PAUSED **");
	mvwprintw(g_vs->info_win, 4, 3, "Cycles/second limit : %-5d", g_vs->speed);
	mvwprintw(g_vs->info_win, 33, 3, "CYCLE_TO_DIE : %-5d", vm->ctd);
	mvwprintw(g_vs->info_win, 35, 3, "CYCLE_DELTA : %-5d", CYCLE_DELTA);
	mvwprintw(g_vs->info_win, 37, 3, "NBR_LIVE : %-5d", NBR_LIVE);
	mvwprintw(g_vs->info_win, 39, 3, "MAX_CHECKS : %-5d", MAX_CHECKS);
	mvwprintw(g_vs->info_win, 27, 3, "Live breakdown for current period :");
	mvwprintw(g_vs->info_win, 30, 3, "Live breakdown for last period :");
	ft_printplayers(vm);
	ft_printlivebar(vm, 0);
	wrefresh(g_vs->info_win);
}

void	ft_speedcontroll(void)
{
	static long long int	prevtime = 0;
	struct timeval			curtime;
	long long int			dusec;

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
			g_vs->speed += g_vs->speed == INT_MAX ? 0 : 10;
		else if (key == '_')
			g_vs->speed -= g_vs->speed < 11 ? 0 : 10;
		nodelay(stdscr, delay);
		ft_printinfo(vm, delay, key);
		key = getch();
		if (delay || (!ft_strchr("-_=+", key) && key > 0))
			break ;
	}
}
