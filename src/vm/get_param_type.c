/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:08:47 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:08:48 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint8_t		get_param1_type(uint8_t opcode, uint8_t tparams)
{
	if ((g_op_tab[opcode].targs[0] & T_IND)
	&& (((tparams & T_FIRST_PARAM) >> 6) & 0x3) == IND_CODE)
	{
		return (T_IND);
	}
	else if ((g_op_tab[opcode].targs[0] & T_REG)
	&& (((tparams & T_FIRST_PARAM) >> 6) & 0x3) == REG_CODE)
	{
		return (T_REG);
	}
	else if ((g_op_tab[opcode].targs[0] & T_DIR)
	&& (((tparams & T_FIRST_PARAM) >> 6) & 0x3) == DIR_CODE)
	{
		return (T_DIR);
	}
	else
	{
		return (0);
	}
}

uint8_t		get_param2_type(uint8_t opcode, uint8_t tparams)
{
	if ((g_op_tab[opcode].targs[1] & T_IND)
	&& (((tparams & T_SECOND_PARAM) >> 4) & 0x3) == IND_CODE)
	{
		return (T_IND);
	}
	else if ((g_op_tab[opcode].targs[1] & T_REG)
	&& (((tparams & T_SECOND_PARAM) >> 4) & 0x3) == REG_CODE)
	{
		return (T_REG);
	}
	else if ((g_op_tab[opcode].targs[1] & T_DIR)
	&& (((tparams & T_SECOND_PARAM) >> 4) & 0x3) == DIR_CODE)
	{
		return (T_DIR);
	}
	else
	{
		return (0);
	}
}

uint8_t		get_param3_type(uint8_t opcode, uint8_t tparams)
{
	if ((g_op_tab[opcode].targs[2] & T_IND)
	&& (((tparams & T_THIRD_PARAM) >> 2) & 0x3) == IND_CODE)
	{
		return (T_IND);
	}
	else if ((g_op_tab[opcode].targs[2] & T_REG)
	&& (((tparams & T_THIRD_PARAM) >> 2) & 0x3) == REG_CODE)
	{
		return (T_REG);
	}
	else if ((g_op_tab[opcode].targs[2] & T_DIR)
	&& (((tparams & T_THIRD_PARAM) >> 2) & 0x3) == DIR_CODE)
	{
		return (T_DIR);
	}
	else
	{
		return (0);
	}
}

uint8_t		get_param_type(uint8_t opcode, uint8_t tparams,
		uint8_t param_number)
{
	if (param_number == 1)
	{
		return (get_param1_type(opcode, tparams));
	}
	else if (param_number == 2)
	{
		return (get_param2_type(opcode, tparams));
	}
	else
	{
		return (get_param3_type(opcode, tparams));
	}
}
