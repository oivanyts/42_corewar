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

typedef struct s_vm
{
	uint32_t last_alive;
}t_vm;

typedef struct s_player
{
	t_threads threads;
	t_header header;
	uint32_t number;
} t_player;

typedef struct s_decoded_op
{
	t_opcode opcode;
	void *args[3];
} t_decoded_op;

t_vm *get_vm(t_vm *vm);

bool load_from_file(char *filename, t_player *player, uint8_t memory[]);

void	players_sort_by_id(t_player *players, uint32_t nplayers);

void	vm_cycle(t_player *players, uint32_t nplayers);

uint8_t decode_tparams(struct s_thread *pc, t_opcode opcode);

void *decode_param(t_opcode opcode, uint8_t tparams, t_thread *pc, uint8_t param_number);

t_decoded_op	op_decode(struct s_thread *pc);

void	op_exec(struct s_thread *pc);

uint32_t threads_alive(t_player *players, uint32_t nplayers);
t_op    op_tab[17];

#endif
