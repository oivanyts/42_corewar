/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 07:21:29 by oivanyts          #+#    #+#             */
/*   Updated: 2019/04/18 07:21:32 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_array_print(int **map, int line, int col)
{
	int i;
	int j;

	i = 0;
	while (i < line)
	{
		j = 0;
		ft_printf("{ ");
		while (j < col)
		{
			ft_printf("%d ", map[i][j]);
			j++;
		}
		ft_printf("}\n");
		i++;
	}
}
