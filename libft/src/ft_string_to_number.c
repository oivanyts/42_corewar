/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_to_number.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:02:35 by oivanyts          #+#    #+#             */
/*   Updated: 2019/05/30 13:02:39 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_string_to_number(char *string, int *n)
{
	*n = ft_atoi(string);
	while (ft_isspace(*string))
	{
		string++;
	}
	return (ft_strlen(string) == (size_t)ft_num_size(*n = ft_atoi(string)));
}
