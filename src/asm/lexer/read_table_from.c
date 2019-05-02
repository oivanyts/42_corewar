#include "asm.h"

static void	create_table(int fd, t_fsm *fsm)
{
	char	*line;
	char	*tmp;
	int		i;

	get_next_line(fd, &line);
	fsm->tab_row = ft_atoi(line);
	tmp = line;
	while (ft_isdigit(*tmp))
		tmp++;
	fsm->tab_col = ft_atoi(tmp);
	free(line);
	fsm->table = (int**)malloc(sizeof(int**) * fsm->tab_row);
	i = 0;
	while (i < fsm->tab_row)
		fsm->table[i++] = (int*)malloc(sizeof(int*) * fsm->tab_col);
}

static void	del_2d_maschar(char **mas)
{
	int		i;

	i = 0;
	while (mas[i] != NULL)
		free(mas[i++]);
	free(mas[i]);
	free(mas);
}

void	del_2d_masint(int **mas, t_fsm *fsm)
{
	int		i;

	i = 0;
	while (i < fsm->tab_row)
		free(mas[i++]);
	free(mas);
}

static void	fill_table(int fd, t_fsm *fsm)
{
	int		col;
	int 	row;
	char	**tmp;
	char	*line;

	row = 0;
	while (row < fsm->tab_row)
	{
		col = 0;
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, '\t');
		free(line);
		while (col < fsm->tab_col)
		{
			fsm->table[row][col] = ft_atoi(tmp[col]);
			col++;
		}
		del_2d_maschar(tmp);
		row++;
	}
}

void		read_table(char *name, t_fsm *fsm)
{
	int		fd;

	fd = open(name, O_RDONLY);
	create_table(fd, fsm);
	fill_table(fd, fsm);
	close(fd);
}