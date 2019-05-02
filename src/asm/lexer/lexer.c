#include "asm.h"
#include "lex_conditions.h"
#include "id_states.h"
#include "lexer.h"

static void	check_errors(t_asm *a)
{
	if (a->token_list != NULL)
		a->errors[1](a);
	if (a->op_list == NULL)
		a->errors[3](a);
}

void		lexer(t_asm *a)
{
	t_fsm			*fsm;

	fsm = a->fsm;
	fsm->curr = fsm->code;
	while (*fsm->curr != '\0')
		finite_state_machine(a, fsm);
	check_errors(a);
	reverse_op_list(&a->op_list);
}

t_op_list	*get_op_list(char *file_name)
{
	t_asm			a;

	init_asm(&a, file_name);
	lexer(&a);
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





































