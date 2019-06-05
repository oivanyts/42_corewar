/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 20:31:02 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 20:31:49 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "stdint.h"

uint8_t					*as_byte(void *ptr);

void					ft_memswap
							(void *dest, void *src, void *buffer, size_t size);

#endif
