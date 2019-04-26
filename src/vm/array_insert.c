/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:14:11 by myaremen          #+#    #+#             */
/*   Updated: 2019/03/14 17:14:12 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

bool	array_push_back(struct s_array *sarr, const void *elem)
{
	if (array_size(sarr) == array_capacity(sarr))
	{
		if (!array_optimal_resize(sarr))
		{
			return (0);
		}
	}
	if (sarr->alloc_func)
	{
		sarr->alloc_func(sarr->arr + sarr->size * sarr->elem_size, elem);
	}
	else
	{
		ft_memcpy(sarr->arr + sarr->size * sarr->elem_size, elem,
				sarr->elem_size);
	}
	sarr->size += 1;
	return (1);
}

bool	array_pop_back(struct s_array *sarr)
{
	if (array_empty(sarr) == 0)
	{
		if (sarr->destroy_func)
		{
			sarr->destroy_func(array_at(sarr, array_size(sarr) - 1));
		}
		sarr->size -= 1;
		return (1);
	}
	else
	{
		return (0);
	}
}

bool	array_pop_front(struct s_array *sarr)
{
	if (array_empty(sarr) == 0)
	{
		if (sarr->destroy_func)
		{
			sarr->destroy_func(array_at(sarr, 0));
		}
		ft_memmove(sarr->arr, sarr->arr + sarr->elem_size,
				(array_size(sarr) - 1) * sarr->elem_size);
		--sarr->size;
		return (1);
	}
	else
	{
		return (0);
	}
}

bool	array_insert(struct s_array *sarr, size_t i, const void *elem)
{
	if (array_find(sarr, elem) != NULL)
	{
		return (0);
	}
	if (array_size(sarr) == array_capacity(sarr))
	{
		if (!array_optimal_resize(sarr))
		{
			return (0);
		}
	}
	ft_memcpy(array_at(sarr, array_size(sarr)), array_at(sarr, i),
			sarr->elem_size);
	ft_memcpy(array_at(sarr, i), elem, sarr->elem_size);
	sarr->size += 1;
	return (1);
}

bool	array_delete(struct s_array *sarr, size_t i)
{
	if (array_empty(sarr) || array_size(sarr) - 1 < i)
	{
		return (0);
	}
	if (sarr->destroy_func)
	{
		sarr->destroy_func(array_at(sarr, i));
	}
	ft_memcpy(array_at(sarr, i), array_at(sarr, array_size(sarr) - 1),
			sarr->elem_size);
	sarr->size -= 1;
	return (1);
}
