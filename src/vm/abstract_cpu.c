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

void    memory_init_number(t_memory *mem, void *ptr, size_t size, uint64_t num)
{
	memory_init(mem, ptr, size);
	ft_memcpy(mem->memory, &num, ft_ullmin(mem->memory_size, sizeof(num)));
}

void    memory_memmove(t_memory *dst, t_memory *src)
{
	ft_memcpy(dst->memory, src->memory, dst->memory_size);
}

void    memory_and(t_memory *dst, t_memory *param1, t_memory *param2)
{
	size_t i;
	size_t size;

	size = ft_ullmin(param1->memory_size, param2->memory_size);
	size = ft_ullmin(size, dst->memory_size);
	i = 0;
	while (i < size)
	{
		as_byte(dst->memory)[i] = as_byte(param1->memory)[i] & as_byte(param2->memory)[i];
		++i;
	}
}

void    memory_or(t_memory *dst, t_memory *param1, t_memory *param2)
{
	size_t i;
	size_t size;

	size = ft_ullmin(param1->memory_size, param2->memory_size);
	size = ft_ullmin(size, dst->memory_size);
	i = 0;
	while (i < size)
	{
		as_byte(dst->memory)[i] = as_byte(param1->memory)[i] | as_byte(param2->memory)[i];
		++i;
	}
}

void    memory_xor(t_memory *dst, t_memory *param1, t_memory *param2)
{
	size_t i;
	size_t size;

	size = ft_ullmin(param1->memory_size, param2->memory_size);
	size = ft_ullmin(size, dst->memory_size);
	i = 0;
	while (i < size)
	{
		as_byte(dst->memory)[i] = as_byte(param1->memory)[i] ^ as_byte(param2->memory)[i];
		++i;
	}
}

void    memory_add(t_memory *dst, t_memory *param1, t_memory *param2)
{
	/*size_t i;
	size_t size;
	bool carry;
	uint8_t res_byte;

	carry = 0;
	size = ft_ullmin(param1->memory_size, param2->memory_size);
	size = ft_ullmin(size, dst->memory_size);
	i = size - 1;
	while (i)
	{
		res_byte = as_byte(param1->memory)[i] + as_byte(param2->memory)[i] + carry;
		carry = ((uint32_t)as_byte(param1->memory)[i] + as_byte(param2->memory)[i] + carry) > 0xFF;
		as_byte(dst->memory)[i] = res_byte;
		--i;
	}
	res_byte = as_byte(param1->memory)[i] + as_byte(param2->memory)[i] + carry;
	carry = ((uint32_t)as_byte(param1->memory)[i] + as_byte(param2->memory)[i] + carry) > 0xFF;
	as_byte(dst->memory)[i] = res_byte;*/
	/*while (carry)
	{

	}*/
	*(uint32_t*)(dst->memory) = *(uint32_t*)(param1->memory) + *(uint32_t*)(param2->memory);
}

void    memory_subtract(t_memory *dst, t_memory *param1, t_memory *param2)
{
	*(uint32_t*)(dst->memory) = *(uint32_t*)(param1->memory) - *(uint32_t*)(param2->memory);
}

bool    memory_iszero(t_memory *mem)
{
	return *(uint32_t*)(mem->memory) == 0;
}

uint32_t memory_tou32(t_memory *mem)
{
	return *(uint32_t*)(mem->memory);
}


void    memory_xprintf(t_memory *mem)
{
	size_t i;

	i = 0;
	while (i < mem->memory_size)
	{
		ft_printf("%x", as_byte(mem->memory)[i]);
		++i;
	}
}
