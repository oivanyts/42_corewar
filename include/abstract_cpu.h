//
// Created by actionfenix on 30.04.19.
//

#ifndef ABSTRACT_CPU_H
# define ABSTRACT_CPU_H

# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct	s_memory
{
	void	*memory;
	size_t	memory_size;
	void	*memory_begin;
	void	*memory_end;
}				t_memory;

void			memory_init(t_memory *mem, void *ptr, size_t size);

void			memory_set_bounds
						(t_memory *mem, void *memory_begin, void *memory_end);

void			memory_init_number(t_memory *mem, uint32_t *num);

void			memory_memmove(t_memory *dst, t_memory *src);

void			memory_and(t_memory *dst, t_memory *param1, t_memory *param2);

void			memory_or(t_memory *dst, t_memory *param1, t_memory *param2);

void			memory_xor(t_memory *dst, t_memory *param1, t_memory *param2);

void			memory_add(t_memory *dst, t_memory *param1, t_memory *param2);

void			memory_subtract
						(t_memory *dst, t_memory *param1, t_memory *param2);

bool			memory_iszero(t_memory *mem);

uint8_t			memory_tou8(t_memory *mem);

uint16_t		memory_tou16(t_memory *mem);

uint32_t		memory_tou32(t_memory *mem);

#endif
