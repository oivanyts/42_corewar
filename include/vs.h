#ifndef VS_H
# define VS_H
# include <ncurses.h>
#define COLOR_GRAY 55
#define BORDER_GRAY 56
#define GRAY	10
#define RED	11
#define GREEN	12
#define YELLOW	13
#define BLUE	14



typedef struct	s_vsmap
{
	int		player;
}				t_vsmap;

typedef struct	s_vs
{
	WINDOW	*mem_win;
	WINDOW	*info_win;
}				t_vs;

t_vsmap	*g_vsmap;
t_vs	*g_vs;
void ft_vsinit();
void	ft_initvsmap(int playern, t_player *player, t_vm *vm);
void	ft_drawmap(t_vm *vm);
#endif
