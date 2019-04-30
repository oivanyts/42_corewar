/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 06:10:41 by oivanyts          #+#    #+#             */
/*   Updated: 2019/04/25 06:12:08 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

const char *error_table[2] =
{
    "No players.",
    "Too many players."
};

void	handle_error(t_error_code n_err)
{
    ft_printf("Error: %s\n", error_table[n_err]);
	exit(n_err);
}
