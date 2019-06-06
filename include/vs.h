/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 09:55:28 by npiatiko          #+#    #+#             */
/*   Updated: 2019/06/05 09:55:29 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VS_H
# define VS_H
# include <ncurses.h>
# include "vm.h"
# define COLOR_GRAY 55
# define BORDER_GRAY 56
# define GRAY	10
# define RED	13
# define GREEN	11
# define CYAN	14
# define BLUE	12
# define LIVE_RED	23
# define LIVE_GREEN	21
# define LIVE_CYAN	24
# define LIVE_BLUE	22
# define WHITE 25
# define SEC 1000000
# define PLAYER_COLOR vm->players[i].number + 10

typedef struct	s_vsmap
{
	int		player;
	int		newdata;
	int		live;
	int		liveplayer;
}				t_vsmap;

typedef struct	s_vs
{
	WINDOW	*mem_win;
	WINDOW	*info_win;
	int		speed;
	int		sumlives;
}				t_vs;

t_vsmap			*g_vsmap;
t_vs			*g_vs;

void			ft_vsinit(t_vm *vm, t_player *players);
void			ft_drawmap(t_vm *vm);
void			ft_changememvs(int memstart, int player);
void			ft_printlivebar(t_vm *vm, int indent);
void			ft_announcewinner(int32_t number, char *name);
void			ft_vsexit(t_error_code n_err);
int				ft_getnchars(int lives);
void			ft_kbhandler(t_vm *vm);
void			ft_initlive(t_thread *sp, int32_t p32);
#endif
