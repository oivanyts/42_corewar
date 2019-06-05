/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_cpu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:25:23 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:25:25 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_cpu.h"
#include "utils.h"
#include "libft.h"

void		memory_subtract(t_memory *dst, t_memory *param1, t_memory *param2)
{
	uint32_t	sum;
	t_memory	res_memory;

	sum = memory_tou32(param1) - memory_tou32(param2);
	memory_init_number(&res_memory, &sum);
	memory_memmove(dst, &res_memory);
}

bool		memory_iszero(t_memory *mem)
{
	return (memory_tou32(mem) == 0);
}

uint8_t		memory_tou8(t_memory *mem)
{
	return (*(uint8_t*)(mem->memory));
}

uint16_t	memory_tou16(t_memory *mem)
{
	uint16_t	u16;

	if ((uint8_t*)mem->memory_end - (uint8_t*)mem->memory >= 2)
	{
		u16 = *(uint16_t*)(mem->memory);
	}
	else
	{
		u16 = (*as_byte(mem->memory) << 8);
		u16 |= *as_byte(mem->memory_begin);
	}
	return (u16);
}

uint32_t	memory_tou32(t_memory *mem)
{
	uint32_t	res;
	uint8_t		i;
	t_memory	mem_cpy;

	mem_cpy = *mem;
	if ((uint8_t*)mem->memory_end - (uint8_t*)mem->memory >= 4)
	{
		res = *(uint32_t*)(mem->memory);
	}
	else
	{
		i = 0;
		res = 0;
		while (i < 4)
		{
			res |= (memory_tou8(&mem_cpy) << ((3 - i) * 8));
			if (mem_cpy.memory == mem_cpy.memory_end)
			{
				mem_cpy.memory = mem_cpy.memory_begin;
			}
			++i;
		}
	}
	return (res);
}
