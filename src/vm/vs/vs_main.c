/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 12:44:52 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/22 18:53:47 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "vs.h"

#define NLINES 10
#define NCOLS 40

int main()
{
	WINDOW *my_wins[2];
	chtype ch;
	int i;

	initscr();
//	cbreak();
//	noecho();
//	keypad(stdscr, TRUE);
	curs_set(0);
	if (!has_colors())
	{
		endwin();
		ft_printf("\nОшибка! Не поддерживаются цвета\n");
		return 1;
	}
	start_color();
	refresh();
	my_wins[0] = newwin(68, 197, 0, 0);
	my_wins[1] = newwin(68, 58, 0, 196);
	init_color(COLOR_GRAY, 355, 355, 355);
	init_pair(10, COLOR_GRAY, COLOR_GRAY);
	init_pair(1, COLOR_RED, 0);
	init_pair(2, COLOR_GREEN, 0);
//	attron(COLOR_PAIR(10));
//	wattron(my_wins[0], COLOR_PAIR(10));
	ch = '*' | COLOR_PAIR(10);
	wborder(my_wins[0], ch, ch, ch, ch, ch, ch, ch, ch);
	wborder(my_wins[1], ch, ch, ch, ch, ch, ch, ch, ch);
	wattron(my_wins[0], COLOR_PAIR(1));
	mvwprintw(my_wins[0], 1, 1, "%s", "test");
	wattron(my_wins[0], COLOR_PAIR(2)|0);
	mvwprintw(my_wins[0], 2, 1, "%d", can_change_color());
	wrefresh(my_wins[0]);
	wrefresh(my_wins[1]);
	refresh();
	getch();
	endwin();
	return 0;
}
//void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);
//int main(int argc, char *argv[])
//{ initscr(); /* Start curses mode */
//	if(has_colors() == FALSE)
//	{ endwin();
//		printf("Your terminal does not support color\n");
//		exit(1);
//	}
//	start_color(); /* Start color */
//	init_pair(1, COLOR_RED, COLOR_BLACK);
//	attron(COLOR_PAIR(1));
//	print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
//	attroff(COLOR_PAIR(1));
//	getch();
//	endwin();
//}
//void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
//{ int length, x, y;
//	float temp;
//	if(win == NULL)
//		win = stdscr;
//	getyx(win, y, x);
//	if(startx != 0)
//		x = startx;
//	if(starty != 0)
//		y = starty;
//	if(width == 0)
//		width = 80;
//	length = strlen(string);
//	temp = (width - length)/ 2;
//	x = startx + (int)temp;
//	mvwprintw(win, y, x, "%s", string);
//	refresh();
//}