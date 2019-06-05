/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_array.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:38:06 by myaremen          #+#    #+#             */
/*   Updated: 2019/04/26 17:38:08 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_ARRAY_H
# define THREAD_ARRAY_H

# include "array.h"
# include "opcalls.h"

typedef struct	s_threads
{
	struct s_array arr;
}				t_threads;

void			threads_init(t_threads *ths);
void			threads_destroy(t_threads *ths);
size_t			threads_size(const t_threads *ths);
t_thread		*threads_at(t_threads *ths, size_t i);
bool			threads_push_back(t_threads *ths, const t_thread *th);

#endif
