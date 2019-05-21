/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:26:50 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/21 19:26:51 by vuslysty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "lexer.h"
#include "disassembler.h"

int	main(void)
{
	t_op_list	*op_list;

	op_list = get_op_list("bots/42.s");
	print_identifiers(op_list);
	system("leaks -q asm");
	return (0);
}
