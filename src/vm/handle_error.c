/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 06:10:41 by oivanyts          #+#    #+#             */
/*   Updated: 2019/05/02 01:38:30 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

const char	*error_table[7] =
{
	"Array sizing failed.",
	"No players.",
	"Too many players.",
	"Wrong magic number in header.",
	"Wrong parameter type passed to command.",
	"Option fail",
 	"File *FILENAME* has too large a code (*SIZE* > 682 bytes)"
};

void	handle_error(t_error_code n_err)
{
	ft_printf("Error: %s\n", error_table[n_err]);
	exit(n_err);
}
