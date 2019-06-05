/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_cpu1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:33:54 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:33:55 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_cpu.h"
#include "libft.h"

void		memory_init(t_memory *mem, void *ptr, size_t size)
{
	mem->memory = ptr;
	mem->memory_size = size;
}

void		memory_set_bounds
	(t_memory *mem, void *memory_begin, void *memory_end)
{
	mem->memory_begin = memory_begin;
	mem->memory_end = memory_end;
}

void		memory_init_number(t_memory *mem, uint32_t *num)
{
	memory_init(mem, num, 4);
	memory_set_bounds(mem, num, num + 1);
}

void		memory_memmove(t_memory *dst, t_memory *src)
{
	size_t		i;
	t_memory	dst_cpy;
	t_memory	src_cpy;

	i = 0;
	dst_cpy = *dst;
	src_cpy = *src;
	while (i < dst->memory_size)
	{
		if (dst_cpy.memory == dst_cpy.memory_end)
		{
			dst_cpy.memory = dst_cpy.memory_begin;
		}
		if (src_cpy.memory == src_cpy.memory_end)
		{
			src_cpy.memory = src_cpy.memory_begin;
		}
		ft_memcpy(dst_cpy.memory, src_cpy.memory, 1);
		dst_cpy.memory += 1;
		src_cpy.memory += 1;
		++i;
	}
}

void		memory_and(t_memory *dst, t_memory *param1, t_memory *param2)
{
	uint32_t	sum;
	t_memory	res_memory;

	sum = memory_tou32(param1) & memory_tou32(param2);
	memory_init_number(&res_memory, &sum);
	memory_memmove(dst, &res_memory);
}
