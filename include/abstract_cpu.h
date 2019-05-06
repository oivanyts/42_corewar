//
// Created by actionfenix on 30.04.19.
//

#ifndef ABSTRACT_CPU_H
# define ABSTRACT_CPU_H

# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct s_memory
{
	void *memory;
	size_t memory_size;
} t_memory;

void    memory_init(t_memory *mem, void *ptr, size_t size);

void    memory_init_number(t_memory *mem, void *ptr, size_t size, uint64_t num);

void    memory_memmove(t_memory *dst, t_memory *src);

void    memory_and(t_memory *dst, t_memory *param1, t_memory *param2);

void    memory_or(t_memory *dst, t_memory *param1, t_memory *param2);

void    memory_xor(t_memory *dst, t_memory *param1, t_memory *param2);

void    memory_add(t_memory *dst, t_memory *param1, t_memory *param2);

void    memory_subtract(t_memory *dst, t_memory *param1, t_memory *param2);

void    memory_xprintf(t_memory *mem);

#endif
