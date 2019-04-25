/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:37:25 by npiatiko          #+#    #+#             */
/*   Updated: 2019/04/25 16:47:52 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h"

int ft_listlen(t_token_list *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return i;
}

void	*ft_checkname(char *name)
{
	int i;

	i = 0;
	while (i < 17)
	{
		if (ft_strequ(name, g_op_tab[i++].name))
			return (NULL);
	}
	return (ft_listlen);
}