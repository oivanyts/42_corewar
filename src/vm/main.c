#include <op.h>
#include "vm.h"

uint8_t	parce_all_players(int num_players, char **filenames, t_header **player)
{
	uint8_t i;

	if (!num_players)
		handle_error(1);
	else if (num_players > 4)
		handle_error(2);
	i = 0;
	while (i < num_players)
	{
		i++;
		load_from_file(filenames[i], i, &player[i - 1]);
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	t_play	players[argc];


	parce_all_players(argc - 1, argv, &players);
	return 0;
}