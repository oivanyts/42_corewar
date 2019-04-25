/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:58:10 by oivanyts          #+#    #+#             */
/*   Updated: 2019/04/25 05:16:33 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_VM_H
#define PROJECT_VM_H

#include "libft.h"

struct s_carriage
{
	uint32_t ip;
	bool cf;
	uint8_t thread;
	uint8_t reg[16];
	bool alive;
	uint8_t wait;
};

struct s_op_data
{
	uint8_t opcode;
};

bool	load_from_file(char	*filename);

void	get_command();

void	decode(struct s_carriage *player);

#endif
