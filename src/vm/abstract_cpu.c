//
// Created by actionfenix on 30.04.19.
//

#include "abstract_cpu.h"
#include "utils.h"
#include "libft.h"

void    memory_init(t_memory *mem, void *ptr, size_t size)
{
	mem->memory = ptr;
	mem->memory_size = size;
}

void	memory_set_bounds(t_memory *mem, void *memory_begin, void *memory_end)
{
	mem->memory_begin = memory_begin;
	mem->memory_end = memory_end;
}

void    memory_init_number(t_memory *mem, uint32_t *num)
{
	memory_init(mem, num, 4);
	memory_set_bounds(mem, num, num + 1);
}

void    memory_memmove(t_memory *dst, t_memory *src)
{
	size_t i;
	t_memory dst_cpy;
	t_memory src_cpy;

	i = 0;
	dst_cpy = *dst;
	src_cpy = *src;
	while (i < dst->memory_size)
	{
		ft_memcpy(dst_cpy.memory, src_cpy.memory, 1);
		if (dst_cpy.memory == dst_cpy.memory_end)
		{
			dst_cpy.memory = dst_cpy.memory_begin;
		}
		if (src_cpy.memory == src_cpy.memory_end)
		{
			src_cpy.memory = src_cpy.memory_begin;
		}
		dst_cpy.memory += 1;
		src_cpy.memory += 1;
		++i;
	}
}

void    memory_and(t_memory *dst, t_memory *param1, t_memory *param2)
{
	uint32_t sum;
	t_memory res_memory;

	sum = memory_tou32(param1) & memory_tou32(param2);
	memory_init_number(&res_memory, &sum);
	memory_memmove(dst, &res_memory);
}

void    memory_or(t_memory *dst, t_memory *param1, t_memory *param2)
{
	uint32_t sum;
	t_memory res_memory;

	sum = memory_tou32(param1) | memory_tou32(param2);
	memory_init_number(&res_memory, &sum);
	memory_memmove(dst, &res_memory);
}

void    memory_xor(t_memory *dst, t_memory *param1, t_memory *param2)
{
	uint32_t sum;
	t_memory res_memory;

	sum = memory_tou32(param1) ^ memory_tou32(param2);
	memory_init_number(&res_memory, &sum);
	memory_memmove(dst, &res_memory);
}

void    memory_add(t_memory *dst, t_memory *param1, t_memory *param2)
{
	uint32_t sum;
	t_memory res_memory;

	sum = memory_tou32(param1) + memory_tou32(param2);
	memory_init_number(&res_memory, &sum);
	memory_memmove(dst, &res_memory);
}

void    memory_subtract(t_memory *dst, t_memory *param1, t_memory *param2)
{
	uint32_t sum;
	t_memory res_memory;

	sum = memory_tou32(param1) - memory_tou32(param2);
	memory_init_number(&res_memory, &sum);
	memory_memmove(dst, &res_memory);
}

bool    memory_iszero(t_memory *mem)
{
	return (memory_tou32(mem) == 0);
}

uint8_t memory_tou8(t_memory *mem)
{
	return (*(uint8_t*)(mem->memory));
}

uint16_t memory_tou16(t_memory *mem)
{
	uint16_t u16;

	if (mem->memory_end - mem->memory >= 2)
	{
		u16 = *(uint16_t*)(mem->memory);
	}
	else
	{
		u16 = (*as_byte(mem) << 8);
		u16 |= *as_byte(mem->memory_begin);
	}
	return (u16);
}

uint32_t memory_tou32(t_memory *mem)
{
	uint32_t res;
	uint8_t i;
	t_memory mem_cpy;

	mem_cpy = *mem;
	if (mem->memory_end - mem->memory >= 4)
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
