/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_big_endian_num.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:27:03 by vuslysty          #+#    #+#             */
/*   Updated: 2019/06/03 18:27:08 by vuslysty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

int			get_int_from_pointer(void *p)
{
	int		num;

	((t_byte*)(&num))[3] = ((t_byte*)(p))[0];
	((t_byte*)(&num))[2] = ((t_byte*)(p))[1];
	((t_byte*)(&num))[1] = ((t_byte*)(p))[2];
	((t_byte*)(&num))[0] = ((t_byte*)(p))[3];
	return (num);
}

int			get_short_from_pointer(void *p)
{
	short		num;

	((t_byte*)(&num))[1] = ((t_byte*)(p))[0];
	((t_byte*)(&num))[0] = ((t_byte*)(p))[1];
	return (num);
}

int			get_char_from_pointer(void *p)
{
	char		num;

	((t_byte*)(&num))[0] = ((t_byte*)(p))[0];
	return (num);
}
