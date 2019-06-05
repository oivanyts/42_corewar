/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 08:02:26 by oivanyts          #+#    #+#             */
/*   Updated: 2019/04/26 08:02:29 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "vm.h"

uint8_t					*as_byte(void *ptr)
{
	return (ptr);
}

void					ft_memswap
	(void *dest, void *src, void *buffer, size_t size)
{
	ft_memcpy(buffer, dest, size);
	ft_memcpy(dest, src, size);
	ft_memcpy(src, buffer, size);
}

unsigned long long int	ft_ullmin
	(unsigned long long int num1, unsigned long long num2)
{
	if (num1 <= num2)
	{
		return (num1);
	}
	else
	{
		return (num2);
	}
}

void		poor_mans_visualization(uint8_t *bytecode)
{
	size_t		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
		{
			ft_printf("0x%04x : ", i);
		}
		ft_printf("%.2x%c", bytecode[i], ' ');
		i++;
		if (!(i % 64) )
		{
			ft_printf("\n");
		}
	}
}
