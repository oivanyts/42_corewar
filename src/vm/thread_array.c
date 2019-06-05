/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:22:20 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:22:28 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_array.h"

void		threads_init(t_threads *ths)
{
	array_init(&ths->arr, sizeof(t_thread), 0, 0);
}

void		threads_destroy(t_threads *ths)
{
	array_destroy(&ths->arr);
}

size_t		threads_size(const t_threads *ths)
{
	return (array_size(&ths->arr));
}

bool		threads_push_back(t_threads *ths, const t_thread *th)
{
	return (array_push_back(&ths->arr, th));
}

t_thread	*threads_at(t_threads *ths, size_t i)
{
	return ((t_thread*)array_at(&ths->arr, i));
}
