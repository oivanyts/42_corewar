#include <op.h>
#include "vm.h"

void poor_mans_visualization(uint8_t *bytecode, t_player *players, int num_players)
{
	size_t   i;
	int      player_gap;
	t_thread *tmp;
	int    color[4] = {31,34,36,32};

	i = 0;
	player_gap = MEM_SIZE / num_players;
	while (i < (size_t)num_players)
	{
		ft_printf("* Player %d, weighing %d, %s, (%s) !\n", i,
				players[i].header.prog_size/8, players[i].header.prog_name,
				players[i].header.comment);
		tmp = players[i].threads.arr.arr;
		ft_printf("carr - [%d][%d] - %d\n", tmp->ip, tmp->id, tmp->reg[0]);
		i++;
	}
	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
		{
			ft_printf("\n");
		}
		if (i == ((t_thread *)players[i / player_gap].threads.arr.arr)->id)
		{
			ft_printf("\033[48;05;%dm", color[i / player_gap] + 10);
		}
		else if (i < players[i / player_gap].header.prog_size + (i / player_gap) * player_gap)
		{
			ft_printf("\033[38;05;%dm", color[i / player_gap]);
		}
		ft_printf("%.2x\033[m ", bytecode[i]);
		i++;
	}
	ft_printf("\n");
}

void alloc_carridge(void *dst, const void *src)
{
	if (!dst)
		dst = ft_memalloc(sizeof(t_thread));
	ft_memcpy(dst, src, sizeof(t_thread));
}

void init_carridge(t_player *player, uint8_t i, uint8_t *memory, int gap)
{
	t_thread	tmp;

	ft_bzero(&tmp, sizeof(t_thread));
	tmp.ip = i;
	tmp.vm_memory = memory;
	tmp.id = (uint32_t)(gap * i);
	tmp.reg[0] = (uint32_t)-i;
	threads_init(&player->threads);
	if (!array_push_back(&player->threads.arr, &tmp))
		handle_error(error_array_add);
}

uint8_t parce_all_players(int num_players, char **filename, t_player *player, uint8_t *memory)
{
	uint8_t		i;
	int			player_gap;

	if (num_players < 1)
		handle_error(error_no_players);
	else if (num_players > MAX_PLAYERS)
		handle_error(error_to_many_players);
	player_gap = MEM_SIZE / num_players;
	i = 0;
	while (i < num_players)
	{
//		ft_printf("Next player starts from : %d\n", i * player_gap);
		load_from_file(filename[i + 1], &player[i], &memory[i *	player_gap]);
		init_carridge(&player[i], i, memory, player_gap);
		i++;
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	t_player	players[argc - 1];
	uint8_t 	memory[MEM_SIZE];

	ft_bzero(players, sizeof(t_player) * (argc - 1));
	ft_bzero(memory, sizeof(uint8_t) * MEM_SIZE);
	parce_all_players(argc - 1, argv, &players[0], &memory[0]);
	poor_mans_visualization(memory, &players[0], argc - 1);
	vm_cycle(&players[0], (uint32_t)(argc - 1));
	return 0;
}
