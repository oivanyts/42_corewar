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

#include "lex_conditions.h"
#include "asm.h"
#include "lexer.h"

int		lex_comment(char *c, char st)
{
	static char	states[] = {1};

	return (str_cmp(c, COMMENT_CMD_STRING) &&
	at_right_state(states, sizeof(states), st));
}

int		lex_whitespace(char *c, char st)
{
	static char	states[] = {1};

	return ((*c == ' ' || *c == '\t') &&
			at_right_state(states, sizeof(states), st));
}

int		lex_endline(char *c, char st)
{
	static char	states[] = {1, 17};

	return (*c == '\n' && at_right_state(states, sizeof(states), st));
}

int		lex_zero(char *c, char st)
{
	static char	states[] = {17, 16};

	return (*c == '\0' && at_right_state(states, sizeof(states), st));
}

int		lex_other(char *c, char st)
{
	if (c || st)
		;
	return (1);
}
