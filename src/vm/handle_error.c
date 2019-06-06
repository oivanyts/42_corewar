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

const char	*g_error_table[11] =
{
	"Cannot open file.",
	"Array sizing failed.",
	"No players.",
	"Too many players.",
	"Can't open file",
	"Wrong magic number in header.",
	"Wrong parameter type passed to command.",
	"Option fail",
	"File has too large a code.",
	"Colors not supported.",
	"Memory doesn't allocate."
};

void	handle_error(t_error_code n_err)
{
	ft_printf("Error: %s\n", g_error_table[n_err]);
	system("leaks -q vm");
	exit(n_err);
}
