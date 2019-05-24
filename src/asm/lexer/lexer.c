/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:26:16 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 13:05:23 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "lex_conditions.h"
#include "id_states.h"
#include "lexer.h"

void		lexer(t_asm *a)
{
	t_fsm			*fsm;

	fsm = a->fsm;
	fsm->curr = fsm->code;
	while (*fsm->curr != '\0')
		finite_state_machine(a, fsm);
	add_to_token_list(&a->token_list, END, NULL, a);
	reverse_token_list(&a->token_list);
	add_to_op_list(&a->op_list, a->token_list);
	a->token_list = NULL;
	reverse_op_list(&a->op_list);
}

t_op_list	*get_op_list(char *file_name)
{
	t_asm			a;

	init_asm(&a, file_name);
	lexer(&a);
	free(a.fsm->code);
	free(a.fsm);
	return (a.op_list);
}

void		print_identifiers(t_op_list *op_list)
{
	t_token_list	*token;

	while (op_list)
	{
		token = op_list->token_list;
		while (token)
		{
			ft_printf("%s ", g_ident_str[token->ident]);
			token = token->next;
		}
		ft_printf("\n");
		op_list = op_list->next;
	}
}
