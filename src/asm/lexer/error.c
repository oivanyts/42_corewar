/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:25:36 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/21 19:25:39 by vuslysty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	err_lex(t_asm *a)
{
	ft_printf("Lexical error at [%i:%i]", a->fsm->st_row, a->fsm->st_col);
	exit(1);
}

void	err_no_endline(t_asm *a)
{
	ft_printf("Syntax error!\n");
	ft_printf("You forgot to put endline at the end of the row [%i].",
			a->fsm->st_row);
	exit(1);
}

void	err_no_closed_quote(t_asm *a)
{
	ft_printf("You have open quote at [%i:%i], but don't have closed quote.",
			a->fsm->st_row, a->fsm->st_col);
	exit(1);
}

void	err_empty_file(t_asm *a)
{
	if (a)
		;
	ft_printf("The file hasn't any instruction.");
	exit(1);
}
