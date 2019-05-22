/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:02:03 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 12:45:51 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_ERRORS_H
# define COREWAR_ERRORS_H

# include "asm.h"

void	err_lex(t_asm *a);
void	err_no_endline(t_asm *a);
void	err_no_closed_quote(t_asm *a);
void	err_empty_file(t_asm *a);

#endif
