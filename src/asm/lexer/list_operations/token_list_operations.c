/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:24:18 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/21 19:24:19 by vuslysty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_to_token_list(t_token_list **token_list, t_identifier ident,
							void *data, t_asm *a)
{
	t_token_list	*tmp;

	tmp = (t_token_list*)ft_memalloc(sizeof(t_token_list));
	tmp->ident = ident;
	tmp->data = data;
	tmp->col = a->fsm->st_col;
	tmp->row = a->fsm->st_row;
	if (*token_list == NULL)
		*token_list = tmp;
	else
	{
		tmp->next = *token_list;
		*token_list = tmp;
	}
}

void	reverse_token_list(t_token_list **token_list)
{
	t_token_list	*prev;
	t_token_list	*next;

	if (*token_list == NULL)
		return ;
	prev = NULL;
	next = (*token_list)->next;
	while (next != NULL)
	{
		(*token_list)->next = prev;
		prev = *token_list;
		*token_list = next;
		next = (*token_list)->next;
	}
	(*token_list)->next = prev;
}
