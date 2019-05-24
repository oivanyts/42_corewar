/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_condition0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:21:52 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 13:05:23 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		lex_num(char *c)
{
	return (ft_isdigit(*c));
}

int		lex_r(char *c)
{
	return (*c == 'r');
}

int		lex_label_chars(char *c)
{
	char	*i;

	i = LABEL_CHARS;
	while (*i != '\0')
	{
		if (*i == *c)
			return (1);
		i++;
	}
	return (0);
}

int		lex_minus(char *c)
{
	return (*c == '-');
}

int		lex_direct_char(char *c)
{
	return (*c == DIRECT_CHAR);
}
