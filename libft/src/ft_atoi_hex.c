/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 01:00:50 by oivanyts          #+#    #+#             */
/*   Updated: 2019/04/12 01:00:54 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static inline bool	ft_ishex(char c)
{
	return (ft_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}

unsigned int		ft_atoi_hex(const char *str)
{
	unsigned long long	x;

	x = 0;
	while (ft_isspace(*str))
		str++;
	if (!(*str++ == '0' && *str++ == 'x'))
	{
		return (0);
	}
	while (*str && ft_ishex(*str))
	{
		x = x << 4;
		if (*str > 64)
			x += ft_toupper(*str) - 55;
		else
			x += (*str - 48);
		str++;
	}
	return (x);
}
