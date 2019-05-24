/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_states.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:15:46 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 13:05:23 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ID_STATES_H
# define ID_STATES_H
# include "asm.h"

int		id_error(t_asm *a);
int		id_indirect(t_asm *a);
int		id_label(t_asm *a);
int		id_instruction(t_asm *a);
int		id_register(t_asm *a);
int		id_direct(t_asm *a);
int		id_direct_label(t_asm *a);
int		id_indirect_label(t_asm *a);
int		id_commentary(t_asm *a);
int		id_separator(t_asm *a);
int		id_string(t_asm *a);
int		id_name(t_asm *a);
int		id_comment(t_asm *a);
int		id_endline(t_asm *a);
int		id_zero(t_asm *a);

#endif
