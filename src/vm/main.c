#include "op.h"
#include "vm.h"
#include "vs.h"

t_list		*find_all_carridges(t_player *player, int num_players)
{
	t_list		*ret;
	t_thread	*tmp;
	int			i;
	int			j;
	int			size;

	ret = NULL;
	i = 0;
	while (i < num_players)
	{
		j = 0;
		size = threads_size(player[i].threads);
		while (j < size)
		{
			tmp = threads_at(player[i].threads, j++);
			ft_lstaddback(&ret, ft_lstnew(&(tmp->ip), sizeof(int)));
		}
		i++;
	}
	return (ret);
}

void		delcarlist(t_list *list)
{
	t_list	*tmp;

	while (list->next)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	free(list);
}

bool		check_pos(size_t i, t_list *list)
{
	while (list)
	{
		if (*(int *)list->content == (int)i)
			return (true);
		list = list->next;
	}
	return (false);
}

void		poor_mans_visualization(uint8_t *bytecode)
{
	size_t		i = 0;
	int			player_gap;
//	t_list		*carridges = NULL;
	t_vm		*vm;

	vm = get_vm(0);

//	int    color[4] = {31,34,36,32};

//	carridges = find_all_carridges(vm->players, vm->nplayers);
	player_gap = MEM_SIZE / vm->nplayers;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
		{
			ft_printf("0x%04x : ", i);
		}
//		if (check_pos(i, carridges))
//		{
//			ft_printf("\033[48;05;%dm", color[i / player_gap] + 10);
//		}
//		else if (i < vm->players[i / player_gap].header.prog_size + (i / player_gap) * player_gap)
//		{
//			ft_printf("\033[38;05;%dm", color[i / player_gap]);
//		}
		ft_printf("%.2x%c", bytecode[i], ' ');
	//ft_printf("\033[m");
		i++;
		if (!(i % 64) )
		{
			ft_printf("\n");
		}
	}
//	delcarlist(carridges);
	//ft_printf("\n");
}

uint8_t		next_file(uint8_t files[4])
{
	uint8_t i;
	uint8_t cp;

	i = 0;
	while (!files[i] && i < 3)
		i++;
	cp = files[i];
	files[i] = 0;
	return (cp);
}

uint8_t		parce_info
	(int argc, char **arguments, t_player *player, uint8_t *memory)
{
	uint8_t		i;
	t_vm		*vm;
	uint8_t		files[4];
	uint16_t	player_gap;

	ft_bzero(&files, sizeof(int) * 4);
	vm = get_vm(0);
	vm->nplayers = 0;
	ft_bzero(vm, sizeof(t_vm));
	handle_options(arguments, argc, vm, &files[0]);
	if (vm->nplayers < 1)
		handle_error(error_no_players);
	else if (vm->nplayers > MAX_PLAYERS)
		handle_error(error_to_many_players);
	player_gap = MEM_SIZE / vm->nplayers;
	threads_init(&vm->threads);
	i = 0;
	while (i < vm->nplayers)
	{
		load_from_file(arguments[next_file(files)], &player[i],
				&memory[(i) * player_gap]);
		player[i].number = i + 1;
		player[i].threads = &vm->threads;
		init_carridge(&player[i], i, memory, player_gap);
		i++;
	}
	return (0);
}

void		init_vm(t_vm *vm, t_player *players, int32_t nplayers)
{
	int32_t player_i;
	int32_t max_player_i;

	player_i = 1;
	max_player_i = 0;
	while (player_i < nplayers)
	{
		if (players[player_i].number > players[max_player_i].number)
		{
			max_player_i = player_i;
		}
		++player_i;
	}
	vm->players = players;
	vm->nplayers = nplayers;
	vm->last_alive = players[max_player_i].number;
	vm->cycle = 1;
}

void		print_players_intro(t_player *players, int32_t nplayers)
{
	int32_t player_i;

	player_i = 0;
	ft_printf("Introducing contestants...\n");
	while (player_i < nplayers)
	{
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
		players[player_i].number, players[player_i].header.prog_size,
		players[player_i].header.prog_name, players[player_i].header.comment);
		++player_i;
	}
}

int			main(int argc, char *argv[])
{
	t_player	players[argc - 1];
	uint8_t		memory[MEM_SIZE];
	t_vm		vm;

	get_vm(&vm);
	ft_bzero(players, sizeof(t_player) * (argc - 1));
	ft_bzero(memory, sizeof(uint8_t) * MEM_SIZE);
	parce_info(argc - 1, argv, &players[0], &memory[0]);
	init_vm(&vm, &players[0], vm.nplayers);
	if (vm.options.visual_ncurses == 0)
		print_players_intro(players, vm.nplayers);
	vm.options.visual_ncurses ? ft_vsinit(&vm, &players[0]) : 0;
	vm_cycle(&vm);
//	if (vm.options.o_dump)
//	{
//		poor_mans_visualization(memory);
//	}
	if (vm.options.visual_ncurses == 0 && !threads_alive(&vm.threads))
		ft_printf("Contestant %d, \"%s\", has won !\n",
				players[vm.last_alive - 1].number,
				players[vm.last_alive - 1].header.prog_name);
	else
		ft_announcewinner(players[vm.last_alive - 1].number,
				players[vm.last_alive - 1].header.prog_name);
	system("leaks -q vm");
	return (0);
}
