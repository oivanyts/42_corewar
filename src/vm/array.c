/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:08:38 by myaremen          #+#    #+#             */
/*   Updated: 2019/02/15 15:08:39 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

void	array_init(struct s_array *sarr, size_t elem_size,
		void (*alloc_elem)(void *ptr, const void *elem), void (*destroy_elem)
		(void *ptr))
{
	sarr->arr = NULL;
	sarr->size = 0;
	sarr->capacity = 0;
	sarr->elem_size = elem_size;
	sarr->alloc_func = alloc_elem;
	sarr->destroy_func = destroy_elem;
}

void	array_destroy(struct s_array *sarr)
{
	size_t i;

	i = 0;
	if (sarr->destroy_func)
	{
		while (i < array_size(sarr))
		{
			sarr->destroy_func(array_at(sarr, i));
			++i;
		}
	}
	free(sarr->arr);
	sarr->arr = 0;
	sarr->size = 0;
	sarr->capacity = 0;
	sarr->elem_size = 0;
	sarr->alloc_func = NULL;
	sarr->destroy_func = NULL;
}

void	array_reverse(struct s_array *sarr)
{
	size_t i;

	if (array_size(sarr) == array_capacity(sarr))
	{
		array_optimal_resize(sarr);
	}
	i = 0;
	while (i < array_size(sarr) / 2)
	{
		ft_memswap(sarr->arr + i * sarr->elem_size, sarr->arr +
		(array_size(sarr) - i - 1) * sarr->elem_size, sarr->arr +
		(array_size(sarr)) * sarr->elem_size, sarr->elem_size);
		++i;
	}
}

bool	array_empty(const struct s_array *sarr)
{
	return (array_size(sarr) == 0);
}

void	array_clear(struct s_array *sarr)
{
	size_t i;

	i = 0;
	if (sarr->destroy_func)
	{
		while (i < array_size(sarr))
		{
			sarr->destroy_func(array_at(sarr, i));
			++i;
		}
	}
	sarr->size = 0;
}
