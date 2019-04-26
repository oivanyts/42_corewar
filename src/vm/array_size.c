/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:12:35 by myaremen          #+#    #+#             */
/*   Updated: 2019/03/14 17:12:37 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

size_t	array_size(const struct s_array *sarr)
{
	return (sarr->size);
}

size_t	array_elem_size(const struct s_array *sarr)
{
	return (sarr->elem_size);
}

size_t	array_capacity(const struct s_array *sarr)
{
	return (sarr->capacity);
}

bool	array_resize(struct s_array *sarr, size_t new_size)
{
	struct s_graph_node *new_arr;

	if (new_size <= array_capacity(sarr))
	{
		return (0);
	}
	new_arr = malloc(new_size * sarr->elem_size);
	if (!new_arr)
	{
		return (0);
	}
	ft_memcpy(new_arr, sarr->arr, array_size(sarr) * sarr->elem_size);
	free(sarr->arr);
	sarr->arr = new_arr;
	sarr->capacity = new_size;
	return (1);
}

bool	array_optimal_resize(struct s_array *sarr)
{
	size_t size;

	size = array_capacity(sarr);
	size = (size_t)(size * 1.2);
	if (size - array_capacity(sarr) < 10)
	{
		size += 10;
	}
	return (array_resize(sarr, size));
}
