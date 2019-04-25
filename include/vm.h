/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:58:10 by oivanyts          #+#    #+#             */
/*   Updated: 2019/04/25 06:19:57 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_VM_H
#define PROJECT_VM_H

#include "libft.h"
#include "op.h"

typedef struct s_carriage
{
	uint32_t ip;
	bool cf;
	uint8_t thread;
	uint8_t reg[16];
	bool alive;
	uint8_t wait;
} t_carriage;

struct s_player
{
	t_carriage carriage;
	t_header header;
};

typedef struct s_decoded_op
{
	uint8_t opcode;
	uint8_t nargs;
	uint32_t *args[3];
} t_decoded_op;

bool	load_from_file(char	*filename, int num, t_header *player);

void	vm_cycle();

t_decoded_op	op_decode(struct s_player *player);

void	op_exec(struct s_decoded_op *data);
void	handle_error(uint8_t n_err);

#endif
