/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_condition1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:22:02 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 13:05:23 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_conditions.h"
#include "asm.h"
#include "lexer.h"

int		lex_separator_char(char *c, char st)
{
	static char	states[] = {1};

	return (*c == SEPARATOR_CHAR && at_right_state(states, sizeof(states), st));
}

int		lex_label_char(char *c, char st)
{
	static char	states[] = {1, 2, 3, 4, 8};

	return (*c == LABEL_CHAR && at_right_state(states, sizeof(states), st));
}

int		lex_commentary(char *c, char st)
{
	static char	states[] = {1};

	return ((*c == COMMENT_CHAR || *c == ALT_COMMENT_CHAR)
			&& at_right_state(states, sizeof(states), st));
}

int		lex_quote(char *c, char st)
{
	static char	states[] = {1, 16};

	return (*c == '"' && at_right_state(states, sizeof(states), st));
}

int		lex_name(char *c, char st)
{
	static char	states[] = {1};

	return (str_cmp(c, NAME_CMD_STRING) &&
			at_right_state(states, sizeof(states), st));
}
