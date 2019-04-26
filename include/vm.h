/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:58:10 by oivanyts          #+#    #+#             */
/*   Updated: 2019/04/25 06:11:07 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_VM_H
#define PROJECT_VM_H

# include "op.h"
# include <stdlib.h>
# include <stdbool.h>

# define T_FIRST_PARAM (uint8_t)0xC0
# define T_SECOND_PARAM (uint8_t)0x30
# define T_THIRD_PARAM (uint8_t)0x0C

typedef enum e_opcode
{
	oplowborder = 0,
	oplive = 1,
	opld,
	opst,
	opadd,
	opsub,
	opand,
	opor,
	opxor,
	opzjmp,
	opldi,
	opsti,
	opfork,
	oplld,
	oplldi,
	oplfork,
	opaff,
	ophighborder
} t_opcode;

typedef struct s_op
{
	void (*op)(uint32_t*, uint32_t*, uint32_t*);
	uint8_t targs[3];
	uint8_t nargs;
} t_op;

static t_op t_ops[ophighborder - 1] =
{

};

typedef struct s_carriage
{
	uint32_t ip;
	bool cf;
	uint8_t thread;
	uint32_t reg[16];
	bool alive;
	uint8_t wait;
} t_carriage;

typedef struct s_player
{
	t_carriage carriage;
	t_header header;
} t_player;

typedef struct s_decoded_op
{
	t_opcode opcode;
	uint32_t *args[3];
} t_decoded_op;

bool	load_from_file(char	*filename, int num);

void	vm_cycle();

uint8_t decode_tparams();

uint32_t *decode_param(t_opcode opcode, uint8_t tparams, t_carriage *pc, uint8_t param_number);

t_decoded_op	op_decode(struct s_carriage *pc);

void	op_exec(struct s_decoded_op *data);

void	handle_error(uint8_t n_err);

inline uint8_t	*as_byte(void *ptr);

#endif
