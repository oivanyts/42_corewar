/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 12:12:05 by oivanyts          #+#    #+#             */
/*   Updated: 2018/10/25 09:38:36 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	long long	*ptr;
	char		*ptr1;
	long long	zero_byte;
	size_t		i;

	zero_byte = 0;
	ptr = s;
	i = n / 8;
	n %= 8;
	while (i--)
		*ptr++ = zero_byte;
	ptr1 = (char *)ptr;
	while (n--)
		*ptr1++ = 0;
}
