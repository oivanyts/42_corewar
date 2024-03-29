/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 20:32:04 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 20:32:12 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_error_code
{
	error_opening_file,
	error_array_add,
	error_no_players,
	error_to_many_players,
	error_read,
	error_wrong_magic,
	error_wrong_tparam,
	error_option,
	error_champ_size,
	error_colors,
	error_memalloc,
	by_user,
	error_nonzero,
	error_diff_size
}				t_error_code;

void			handle_error(t_error_code n_err);

const char		*g_error_table[14];

#endif
