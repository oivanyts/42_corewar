/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:58:10 by oivanyts          #+#    #+#             */
/*   Updated: 2019/05/01 22:52:15 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_VM_H
#define PROJECT_VM_H

# include "op.h"
# include "opcalls.h"
# include "libft.h"
# include "thread_array.h"
# include "error.h"
# include "utils.h"

#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)

# define T_FIRST_PARAM (uint8_t)0xC0
# define T_SECOND_PARAM (uint8_t)0x30
# define T_THIRD_PARAM (uint8_t)0x0C

# define OPTIONS "d:n:s:vc"

typedef struct	s_player
{
	t_threads	*threads;
	t_header	header;
	int32_t		number;
} 				t_player;

typedef struct	s_vm
{
	t_player	*players;
	int32_t		nplayers;
	t_threads	threads;
	uint32_t	last_alive;
	uint32_t	cycle;
	bool		o_dump;
	uint32_t	o_dump_point;
	bool		o_stop;
	uint32_t	o_stop_point;
	uint8_t		o_next_player;
	bool		visual;
}				t_vm;


t_vm			*get_vm(t_vm *vm);

bool			load_from_file(char *filename, t_player *player, uint8_t memory[]);

void	vm_cycle(t_vm *vm);

uint8_t get_param_type(uint8_t opcode, uint8_t tparams, uint8_t param_number);

uint8_t decode_tparams(struct s_thread *pc, uint8_t opcode);

t_memory decode_param(t_decoded_op op, t_thread *pc, uint8_t param_number);

void	op_decode(t_thread *pc);

void	op_exec(t_thread *pc);

uint32_t threads_alive(t_threads *threads);

t_op    op_tab[17];

void init_carridge(t_player *player, uint8_t i, uint8_t *memory, int gap);

void poor_mans_visualization(uint8_t *bytecode, t_player *players, int num_players);

int get_options(int	argc, char *argv[], const char *options);

#endif
