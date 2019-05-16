#include "op.h"
#include "vm.h"



t_list *find_all_carridges(t_player *pPlayer, int num_players)
{
	t_list	*ret = NULL;
	int 	i = 0, size, j;
	t_thread	*tmp;

	while (i < num_players)
	{
		j = 0;
		size = threads_size(&pPlayer[i].threads);
		while (j < size)
		{
			tmp = threads_at(&pPlayer[i].threads, j++);
			ft_lstaddback(&ret, ft_lstnew(&(tmp->ip), sizeof(int)));
		}
		i++;
	}
	return ret;
}

void delcarlist(t_list *pList)
{
	t_list	*tmp;
	while (pList->next)
	{
		tmp = pList;
		pList = pList->next;
		free(tmp);
	}
	free(pList);
}


bool check_pos(size_t i, t_list *pList)
{
	while (pList)
	{
		if (*(int *)pList->content == (int)i)
			return (true);
		pList = pList->next;
	}
	return (false);
}

void poor_mans_visualization(uint8_t *bytecode, t_player *players, int num_players)
{
	size_t		i;
	int			player_gap;
//	t_thread	*tmp;
	t_list		*carridges = NULL;

	int    color[4] = {31,34,36,32};

	carridges = find_all_carridges(players, num_players);
	i = 0;
	player_gap = MEM_SIZE / num_players;
//	while (i < (size_t)num_players)
//	{
//		ft_printf("* Player %d, weighing %d, %s, (%s) !\n", i,
//				players[i].header.prog_size/8, players[i].header.prog_name,
//				players[i].header.comment);
//		tmp = players[i].threads.arr.arr;
//		ft_printf("carr - [%d][%d] - %d\n", tmp->ip, players->number, tmp->reg[0]);
//		i++;
//	}
	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
		{
			ft_printf("\n0x%04x : ", i);
		}
//		if (i == ((t_thread *)players[i / player_gap].threads.arr.arr)->ip)
		if (check_pos(i, carridges))
		{
			ft_printf("\033[48;05;%dm", color[i / player_gap] + 10);
		}
		else if (i < players[i / player_gap].header.prog_size + (i / player_gap) * player_gap)
		{
			ft_printf("\033[38;05;%dm", color[i / player_gap]);
		}
		//ft_printf("[%d]%.2x\033[m ", i, bytecode[i]);
		ft_printf("%.2x\033[m%c", bytecode[i], (i + 1) % 64 ? ' ' : 1);
		i++;
	}
	delcarlist(carridges);
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
	player_gap = MEM_SIZE / num_players;
	i = 0;
	while (i < num_players)
	{
//		ft_printf("Next player starts from : %d\n", i * player_gap);
		load_from_file(filename[i + 1], &player[i], &memory[i *	player_gap]);
		player[i].number = i + 1;
		threads_init(&player[i].threads);
		init_carridge(&player[i], i, memory, player_gap);
		i++;
	}
	return (0);
}

void init_vm(t_vm *vm, t_player *players, int32_t nplayers)
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
	vm->cycle = 0; //1?
}

char **read_options(int argc, char **argv)
{
	(void)argc;
	return argv;
}

int		main(int argc, char *argv[])
{
	t_player	players[argc - 1];
	uint8_t 	memory[MEM_SIZE];
	t_vm vm;

	get_vm(&vm);
	ft_bzero(players, sizeof(t_player) * (argc - 1));
	ft_bzero(memory, sizeof(uint8_t) * MEM_SIZE);
//	argv = get_options(argc, argv, OPTIONS);								//
	parce_all_players(argc - 1, argv, &players[0], &memory[0]);
	//poor_mans_visualization(memory, &players[0], argc - 1);
	init_vm(&vm, &players[0], argc - 1);
	vm_cycle(vm.players, vm.nplayers);
	poor_mans_visualization(memory, &players[0], argc - 1);
	printf("Last player alive: %u\n", vm.last_alive);
	return 0;
}
