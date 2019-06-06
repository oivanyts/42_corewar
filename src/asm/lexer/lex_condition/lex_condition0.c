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

#include "lex_conditions.h"
#include "asm.h"

int		lex_num(char *c, char st)
{
	static char	states[] = {1, 2, 4, 5, 6, 7, 8, 9, 10, 11};

	return (ft_isdigit(*c) && at_right_state(states, sizeof(states), st));
}

int		lex_r(char *c, char st)
{
	static char	states[] = {1};

	return (*c == 'r' && at_right_state(states, sizeof(states), st));
}

int		lex_label_chars(char *c, char st)
{
	char	*i;
	static char	states[] = {1, 2, 3, 4, 5, 12, 13, 14, 15};


	i = LABEL_CHARS;
	while (*i != '\0')
	{
		if (*i == *c)
			return (at_right_state(states, sizeof(states), st));
		i++;
	}
	return (0);
}

int		lex_minus(char *c, char st)
{
	static char	states[] = {1, 8};

	return (*c == '-'  && at_right_state(states, sizeof(states), st));
}

int		lex_direct_char(char *c, char st)
{
	static char	states[] = {1};

	return (*c == DIRECT_CHAR  && at_right_state(states, sizeof(states), st));
}
