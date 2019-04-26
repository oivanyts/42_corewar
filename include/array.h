/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:08:29 by myaremen          #+#    #+#             */
/*   Updated: 2019/02/15 15:08:31 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include <stdlib.h>
# include <stdbool.h>
# include <stddef.h>
# include "libft.h"

# define NPOS ((size_t)-1)

struct	s_array
{
	void	*arr;
	size_t	size;
	size_t	capacity;
	size_t	elem_size;
	void	(*alloc_func)(void *ptr, const void *elem);
	void	(*destroy_func)(void *ptr);
};

void	array_init(struct s_array *sarr, size_t elem_size,
		void (*alloc_elem)(void *ptr, const void *elem),
		void (*destroy_elem)(void *ptr));

void	array_destroy(struct s_array *arr);

size_t	array_size(const struct s_array *arr);

size_t	array_elem_size(const struct s_array *arr);

size_t	array_capacity(const struct s_array *arr);

bool	array_resize(struct s_array *sarr, size_t new_size);

void	*array_find(struct s_array *sarr, const void *elem);

size_t	array_find_i(struct s_array *sarr, const void *elem);

void	*array_at(struct s_array *sarr, size_t i);

bool	array_push_back(struct s_array *sarr, const void *elem);

bool	array_pop_back(struct s_array *sarr);

bool	array_pop_front(struct s_array *sarr);

void	*array_back(struct s_array *sarr);

void	*array_front(struct s_array *sarr);

void	array_reverse(struct s_array *sarr);

bool	array_empty(const struct s_array *sarr);

bool	array_insert(struct s_array *sarr, size_t i, const void *elem);

bool	array_delete(struct s_array *sarr, size_t i);

void	array_clear(struct s_array *sarr);

bool	array_optimal_resize(struct s_array *sarr);

#endif
