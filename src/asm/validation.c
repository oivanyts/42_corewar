/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:37:25 by npiatiko          #+#    #+#             */
/*   Updated: 2019/04/26 14:05:37 by npiatiko         ###   ########.fr       */
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

t_op	*ft_checkname(char *name)
{
	int i;

	i = 0;
	while (i < 17)
	{
		if (ft_strequ(name, g_op_tab[i].name))
			return (&g_op_tab[i]);
		i++;
	}
	return (NULL);
}

void 	ft_chekargs(t_token_list *lst)
{
	int i;

	i = 1;
	while (lst)
	{

		lst = lst->next;
		i++;
	}
}

void	ft_validation (t_op_list *oplist)
{
	t_op *op;

	if (!(op = ft_checkname((char *)(oplist->token_list->data))))
		exit(8);
	if (ft_listlen(oplist->token_list) != op->args * 2)
		exit(7);
	ft_chekargs(oplist->token_list);
}