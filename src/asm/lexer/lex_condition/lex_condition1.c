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

#include "asm.h"
#include "lexer.h"

int		lex_separator_char(char *c)
{
	return (*c == SEPARATOR_CHAR);
}

int		lex_label_char(char *c)
{
	return (*c == LABEL_CHAR);
}

int		lex_commentary(char *c)
{
	return (*c == COMMENT_CHAR || *c == ALT_COMMENT_CHAR);
}

int		lex_quote(char *c)
{
	return (*c == '"');
}

int		lex_name(char *c)
{
	return (str_cmp(c, NAME_CMD_STRING));
}
