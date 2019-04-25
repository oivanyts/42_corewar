#include <op.h>
#include "vm.h"

uint8_t	parce_all_players(int num_players, char **filenames, t_header **player)
{
	if (num_players)

	return (true);
}
int		main(int argc, char *argv[])
{
	t_header	players[argc];

	if (!(parce_all_players(argc, argv, &players)))
	load_from_file(argv[1], argc);
	ft_printf("#%d players {red}[%s] {green}[%s] {cyan}[%s] {blue}[%s]{eoc}\n", argc, argv[1], argv[2], argv[3], argv[4]);
	return 0;
}