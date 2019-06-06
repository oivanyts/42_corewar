/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_conditions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:16:50 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 13:05:23 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_CONDITIONS_H
# define LEX_CONDITIONS_H

int		lex_num(char *c, char state);
int		lex_r(char *c, char state);
int		lex_label_chars(char *c, char state);
int		lex_minus(char *c, char state);
int		lex_direct_char(char *c, char state);
int		lex_separator_char(char *c, char state);
int		lex_label_char(char *c, char state);
int		lex_comment(char *c, char state);
int		lex_quote(char *c, char state);
int		lex_name(char *c, char state);
int		lex_commentary(char *c, char state);
int		lex_whitespace(char *c, char state);
int		lex_endline(char *c, char state);
int		lex_zero(char *c, char state);
int		lex_other(char *c, char state);
int 	lex_instruction(char *c, char st);
int		at_right_state(char *mas, int len, char curr_state);

#endif
