#include "op.h"
#include "vm.h"
#include "vs.h"

#define TOFILE //

t_list *find_all_carridges(t_player *pPlayer, int num_players)
{
	t_list	*ret = NULL;
	int 	i = 0, size, j;
	t_thread	*tmp;

	while (i < num_players)
	{
		j = 0;
		size = threads_size(pPlayer[i].threads);
		while (j < size)
		{
			tmp = threads_at(pPlayer[i].threads, j++);
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
	size_t		i = 0;
	int			player_gap;
//	t_thread	*tmp;
	t_list		*carridges = NULL;

	//int    color[4] = {31,34,36,32};

	carridges = find_all_carridges(players, num_players);
	player_gap = MEM_SIZE / num_players;
//	while (i < (size_t)num_players)
//	{
//		ft_printf("* Player %d, weighing %d, %s, (%s) !\n", players[i].number,
//				players[i].header.prog_size/8, players[i].header.prog_name,
//				players[i].header.comment);
//		tmp = players[i].threads.arr.arr;
//		ft_printf("carr - [%d][%d] - %d\n", tmp->ip, players->number, tmp->reg[0]);
//		i++;
//	}
//	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
		{
			ft_printf("0x%04x : ", i);
		}
		if (check_pos(i, carridges))
		{
			//ft_printf("\033[48;05;%dm", color[i / player_gap] + 10);
		}
		else if (i < players[i / player_gap].header.prog_size + (i / player_gap) * player_gap)
		{
//			ft_printf("\033[38;05;%dm", color[i / player_gap]);
		}
		ft_printf("%.2x%c", bytecode[i], ' ');
	//ft_printf("\033[m");
		i++;
		if (!(i % 64) )
		{
			ft_printf("\n");
		}
	}
	delcarlist(carridges);
	//ft_printf("\n");
}

bool string_to_number(char *string, int *n)
{
	*n = ft_atoi(string);
	while (ft_isspace(*string))
	{
		string++;
	}
	return (ft_strlen(string) == (size_t)ft_num_size(*n = ft_atoi(string)));
}

bool is_option(char **argv, uint8_t *arg_num, char string1[])
{
	char	*option;
	int		param;
	t_vm	*vm;

	vm = get_vm(0);
	if (argv[*arg_num][0] != '-')
		return (false);
	if ((option = ft_strstr(string1, &argv[*arg_num][1])))
	{
		vm->o_next_player = 0;
		(*arg_num)++;
		if (*(option + 1) == ':')
		{
			if (string_to_number(argv[*arg_num], &param))
			{
				(*arg_num)++;
			}
			else
			{

			}
			if (ft_strnequ(option, "d", 1))
			{
				vm->o_dump = true;
				vm->o_dump_point = param;
			}
			else if (ft_strnequ(option, "s", 1))
			{
				vm->o_stop = true;
				vm->o_stop_point = param;
			}
			else if (ft_strnequ(option, "n", 1))
			{
				if (param > 4 || param < 1)
					handle_error(error_option);
				vm->o_next_player = param;
			}
			else
			{
				handle_error(error_option);
			}
		}
		else
		{
			//vm & other param
		}
	}
	return (true);
}

int place_process(uint8_t *files, uint8_t o_numb, uint8_t i)
{
	int8_t	drag;

	if (o_numb)
	{
		if (files[o_numb - 1])
		{
			drag = 3;
			while (drag > (o_numb - 1))
			{
				files[drag] = files[drag - 1];
				drag--;
			}
		}
		files[o_numb - 1] = i;
	}
	else
	{
		drag = 0;
		while (files[drag] && drag < 3)
			drag++;
		files[drag] = i;
	}
	return 0;
}

uint8_t next_file(uint8_t files[4])
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

uint8_t parce_info(int argc, char **arguments, t_player *player, uint8_t *memory)
{
	uint8_t		i;
	t_vm		*vm;
	uint8_t 	files[4];
	int 		player_gap;
//	int			numbers[4];

//	ft_bzero(&numbers, sizeof(int) * 4);
	ft_bzero(&files, sizeof(int) * 5);
	vm = get_vm(0);
	vm->nplayers = 0;

	i = 1;
	ft_bzero(vm, sizeof(t_vm));
	while (i <= argc)
	{
		if (is_option(arguments, &i, OPTIONS))
		{
			continue ;
		}
		else
		{

		}
//		chose_player_number();
		place_process(&files[0], vm->o_next_player, i);
		vm->o_next_player = 0;
		vm->nplayers++;
		i++;
	}
	if (vm->nplayers < 1)
		handle_error(error_no_players);
	else if (vm->nplayers > MAX_PLAYERS)
		handle_error(error_to_many_players);
	player_gap = MEM_SIZE / vm->nplayers;
	threads_init(&vm->threads);
	i = 0;
	while (i < vm->nplayers)
	{
		load_from_file(arguments[next_file(files)], &player[i], &memory[(i) * player_gap]);
		player[i].number = i + 1;
		player[i].threads = &vm->threads;
		init_carridge(&player[i], i, memory, player_gap);
//		ft_initvsmap(i, player, vm);
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
	vm->cycle = 1;
}

int		main(int argc, char *argv[])
{
	t_player	players[argc - 1];
	uint8_t 	memory[MEM_SIZE];
	t_vm vm;

	get_vm(&vm);
	ft_bzero(players, sizeof(t_player) * (argc - 1));
	ft_bzero(memory, sizeof(uint8_t) * MEM_SIZE);
//	ft_vsinit();
	parce_info(argc - 1, argv, &players[0], &memory[0]);
//	ft_drawmap(&memory[0]);
//	ft_printf("Introducing contestants...\n"
//			  "* Player 1, weighing 23 bytes, \"zork\" (\"just a basic living prog\") !\n"
//			  "* Player 2, weighing 325 bytes, \"Celebration Funebre v0.99pl42\" (\"Jour J\") !\n"
//			  "* Player 3, weighing 281 bytes, \"Tching tching(Intercepteur), Bouh!Bouh!(bruits d'anti-jeu)\" (\"\") !\n");
	//poor_mans_visualization(memory, &players[0], vm.nplayers);
	init_vm(&vm, &players[0], vm.nplayers);
	vm_cycle(&vm);
//	poor_mans_visualization(memory, &players[0], vm.nplayers);
//	printf("Last player alive: %u\n", vm.last_alive);
	return 0;
}
