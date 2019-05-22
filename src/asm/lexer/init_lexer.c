/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:26:00 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 12:45:51 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "lex_conditions.h"
#include "id_states.h"
#include "errors.h"
#include "lexer.h"

static void	init_lex_conditions(t_asm *a)
{
	a->lex_condition[0] = lex_whitespace;
	a->lex_condition[1] = lex_num;
	a->lex_condition[2] = lex_r;
	a->lex_condition[3] = lex_endline;
	a->lex_condition[4] = lex_minus;
	a->lex_condition[5] = lex_direct_char;
	a->lex_condition[6] = lex_separator_char;
	a->lex_condition[7] = lex_label_char;
	a->lex_condition[8] = lex_commentary;
	a->lex_condition[9] = lex_quote;
	a->lex_condition[10] = lex_zero;
	a->lex_condition[11] = lex_label_chars;
	a->lex_condition[12] = lex_name;
	a->lex_condition[13] = lex_comment;
	a->lex_condition[14] = lex_other;
}

static void	init_id_states(t_asm *a)
{
	a->id_state[1] = id_indirect;
	a->id_state[2] = id_label;
	a->id_state[3] = id_instruction;
	a->id_state[4] = id_register;
	a->id_state[5] = id_direct;
	a->id_state[6] = id_direct_label;
	a->id_state[7] = id_separator;
	a->id_state[8] = id_indirect_label;
	a->id_state[9] = id_commentary;
	a->id_state[10] = id_string;
	a->id_state[11] = id_name;
	a->id_state[12] = id_comment;
	a->id_state[13] = id_endline;
	a->id_state[14] = id_zero;
}

static void	init_errors(t_asm *a)
{
	a->errors[0] = err_lex;
	a->errors[1] = err_no_endline;
	a->errors[2] = err_no_closed_quote;
	a->errors[3] = err_empty_file;
}

void		init_asm(t_asm *a, char *file_name)
{
	a->row = 1;
	a->col = 1;
	a->fsm = (t_fsm*)ft_memalloc(sizeof(t_fsm));
	a->fsm->code = read_text_from(file_name);
	a->fsm->state = 1;
	a->op_list = NULL;
	a->token_list = NULL;
	init_lex_conditions(a);
	init_id_states(a);
	init_errors(a);
}
