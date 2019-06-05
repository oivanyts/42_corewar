//
// Created by Nickolay PIATIKOP on 2019-06-05.
//

#include "abstract_cpu.h"

void		memory_or(t_memory *dst, t_memory *param1, t_memory *param2)
{
	uint32_t	sum;
	t_memory	res_memory;

	sum = memory_tou32(param1) | memory_tou32(param2);
	memory_init_number(&res_memory, &sum);
	memory_memmove(dst, &res_memory);
}

void		memory_xor(t_memory *dst, t_memory *param1, t_memory *param2)
{
	uint32_t	sum;
	t_memory	res_memory;

	sum = memory_tou32(param1) ^ memory_tou32(param2);
	memory_init_number(&res_memory, &sum);
	memory_memmove(dst, &res_memory);
}

void		memory_add(t_memory *dst, t_memory *param1, t_memory *param2)
{
	uint32_t	sum;
	t_memory	res_memory;

	sum = memory_tou32(param1) + memory_tou32(param2);
	memory_init_number(&res_memory, &sum);
	memory_memmove(dst, &res_memory);
}
