#ifndef VS_H
# define VS_H
# include <ncurses.h>
#define COLOR_GRAY 55
#define BORDER_GRAY 56
#define GRAY	10
#define RED	13
#define GREEN	11
#define CYAN	14
#define BLUE	12
#define LIVE_RED	23
#define LIVE_GREEN	21
#define LIVE_CYAN	24
#define LIVE_BLUE	22
#define WHITE 25
#define SEC 1000000


typedef struct	s_vsmap
{
	int		player;
	int 	newdata;
	int		live;
	int 	liveplayer;
}				t_vsmap;

typedef struct	s_vs
{
	WINDOW	*mem_win;
	WINDOW	*info_win;
	int		speed;
}				t_vs;

t_vsmap	*g_vsmap;
t_vs	*g_vs;
void	ft_vsinit();
void	ft_initvsmap(int playern, t_player *player, t_vm *vm);
void	ft_drawmap(t_vm *vm);
void	ft_changememvs(int memstart, int player);
void    foreach_thread(t_threads *threads, void(*func)(t_thread*));
#endif
