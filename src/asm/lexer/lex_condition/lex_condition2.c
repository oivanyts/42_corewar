/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_condition2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:22:13 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 13:05:23 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "lexer.h"

int		lex_comment(char *c)
{
	return (str_cmp(c, COMMENT_CMD_STRING));
}

int		lex_whitespace(char *c)
{
	return (*c == ' ' || *c == '\t');
}

int		lex_endline(char *c)
{
	return (*c == '\n');
}

int		lex_zero(char *c)
{
	return (*c == '\0');
}

int		lex_other(char *c)
{
	if (c)
		;
	return (1);
}
