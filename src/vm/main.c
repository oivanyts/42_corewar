#include <op.h>
#include "vm.h"

void output_field(uint8_t *bytecode, size_t size, t_player players[], int num_players)
{
	size_t i;
	int			player_gap;

	i = 0;
	player_gap = MEM_SIZE / num_players;
	ft_printf("{green}%c", 1);
	while (i < size)
	{
		ft_printf("%.2x ", bytecode[i]);
		i++;
		if (!(i % 64))
			ft_printf("\n");
		if (i == players[i / player_gap].header.prog_size  + (i / player_gap) * player_gap)
			ft_printf("\033[0m");
		if (!(i % player_gap))
			ft_printf("{green}%c", 1);
	}
	ft_printf("\n");
}

uint8_t parce_all_players(int num_players, char **filename, t_player *player, uint8_t *memory)
{
	uint8_t		i;
	int			player_gap;

	if (num_players < 1)
		handle_error(error_no_players);
	else if (num_players > MAX_PLAYERS)
		handle_error(error_to_many_players);
	ft_printf("gap = %d\n", player_gap = MEM_SIZE / num_players);
	i = 0;
	while (i < num_players)
	{
		ft_printf("Next player starts from : %d\n", i * player_gap);
		load_from_file(filename[i +
								1], &player[i], &memory[i *
														player_gap]);
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
	output_field(memory, MEM_SIZE, &players[0], argc - 1);
	vm_cycle(&players[0], argc - 1);
	return 0;
}