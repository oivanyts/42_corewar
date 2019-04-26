/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:16:47 by myaremen          #+#    #+#             */
/*   Updated: 2019/03/14 17:16:49 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

void	*array_find(struct s_array *sarr, const void *elem)
{
	size_t i;

	i = 0;
	while (i < sarr->size * sarr->elem_size)
	{
		if (ft_memcmp(sarr->arr + i, elem, sarr->elem_size) == 0)
		{
			return (sarr->arr + i);
		}
		i += sarr->elem_size;
	}
	return (NULL);
}

size_t	array_find_i(struct s_array *sarr, const void *elem)
{
	size_t i;

	i = 0;
	while (i < sarr->size * sarr->elem_size)
	{
		if (ft_memcmp(sarr->arr + i, elem, sarr->elem_size) == 0)
		{
			return (i / sarr->elem_size);
		}
		i += sarr->elem_size;
	}
	return (NPOS);
}

void	*array_at(struct s_array *sarr, size_t i)
{
	if (i < array_size(sarr))
	{
		return (sarr->arr + i * sarr->elem_size);
	}
	else
	{
		return (NULL);
	}
}

void	*array_back(struct s_array *sarr)
{
	if (array_empty(sarr))
	{
		return (NULL);
	}
	return (array_at(sarr, array_size(sarr) - 1));
}

void	*array_front(struct s_array *sarr)
{
	if (array_empty(sarr))
	{
		return (NULL);
	}
	return (array_at(sarr, 0));
}
