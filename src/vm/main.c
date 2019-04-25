#include <op.h>
#include "vm.h"

uint8_t	parce_all_players(int num_players, char **filenames, t_player player[])
{
	uint8_t i;

	if (num_players < 2)
		handle_error(1);
	else if (num_players > 4)
		handle_error(2);
	i = 0;
	while (i < num_players)
	{
		load_from_file(filenames[i + 1], i, &player[i]);
		i++;
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	t_player	players[argc];


	parce_all_players(argc - 1, argv, &players[0]);
	return 0;
}