//
// Created by actionfenix on 30.04.19.
//

#ifndef UTILS_H
# define UTILS_H
# include "stdint.h"

uint8_t					*as_byte(void *ptr);
void					ft_memswap
							(void *dest, void *src, void *buffer, size_t size);
unsigned long long int	ft_ullmin
						(unsigned long long int num1, unsigned long long num2);

#endif
