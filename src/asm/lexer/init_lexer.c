#include "asm.h"
#include "lex_conditions.h"
#include "id_states.h"
#include "lexer.h"

void	init_lex_conditions(t_asm *a)
{
	a->lex_condition[0] = lex_whitespace;
	a->lex_condition[1] = lex_num;
	a->lex_condition[2] = lex_r;
	a->lex_condition[3] = lex_label_chars;
	a->lex_condition[4] = lex_minus;
	a->lex_condition[5] = lex_direct_char;
	a->lex_condition[6] = lex_separator_char;
	a->lex_condition[7] = lex_label_char;
	a->lex_condition[8] = lex_comment_endline;
	a->lex_condition[9] = lex_quote;
	a->lex_condition[10] = lex_name;
	a->lex_condition[11] = lex_comment;
	a->lex_condition[12] = lex_other;
}

void	init_id_states(t_asm *a)
{
	a->id_state[0] = id_error;
	a->id_state[1] = id_indirect;
	a->id_state[2] = id_label;
	a->id_state[3] = id_instruction;
	a->id_state[4] = id_register;
	a->id_state[5] = id_direct;
	a->id_state[6] = id_direct_label;
	a->id_state[7] = id_separator;
	a->id_state[8] = id_indirect_label;
	a->id_state[9] = id_comment_endline;
	a->id_state[10] = id_string;
	a->id_state[11] = id_name;
	a->id_state[12] = id_comment;
}

void	init_fsm(t_asm *a, char *name)
{
	a->fsm->code = read_text_from(name);
	read_table("machine", a->fsm);
	a->fsm->state = 1;
}

void	init_asm(t_asm *a, char *file_name)
{
	a->row = 1;
	a->col = 1;
	a->fsm = (t_fsm*)ft_memalloc(sizeof(t_fsm));
	init_fsm(a, file_name);
	a->op_list = NULL;
	a->token_list = NULL;
	init_lex_conditions(a);
	init_id_states(a);
}