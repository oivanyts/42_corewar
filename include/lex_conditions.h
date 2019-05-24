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

int		lex_num(char *c);
int		lex_r(char *c);
int		lex_label_chars(char *c);
int		lex_minus(char *c);
int		lex_direct_char(char *c);
int		lex_separator_char(char *c);
int		lex_label_char(char *c);
int		lex_comment(char *c);
int		lex_quote(char *c);
int		lex_name(char *c);
int		lex_commentary(char *c);
int		lex_whitespace(char *c);
int		lex_endline(char *c);
int		lex_zero(char *c);
int		lex_other(char *c);

#endif
