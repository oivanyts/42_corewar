/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_force_param_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:09:20 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:09:22 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint8_t		get_force_param1_type(uint8_t tparams)
{
	if ((((tparams & T_FIRST_PARAM) >> 6) & 0x3) == IND_CODE)
	{
		return (T_IND);
	}
	else if ((((tparams & T_FIRST_PARAM) >> 6) & 0x3) == REG_CODE)
	{
		return (T_REG);
	}
	else if ((((tparams & T_FIRST_PARAM) >> 6) & 0x3) == DIR_CODE)
	{
		return (T_DIR);
	}
	else
	{
		return (0);
	}
}

uint8_t		get_force_param2_type(uint8_t tparams)
{
	if ((((tparams & T_SECOND_PARAM) >> 4) & 0x3) == IND_CODE)
	{
		return (T_IND);
	}
	else if ((((tparams & T_SECOND_PARAM) >> 4) & 0x3) == REG_CODE)
	{
		return (T_REG);
	}
	else if ((((tparams & T_SECOND_PARAM) >> 4) & 0x3) == DIR_CODE)
	{
		return (T_DIR);
	}
	else
	{
		return (0);
	}
}

uint8_t		get_force_param3_type(uint8_t tparams)
{
	if ((((tparams & T_THIRD_PARAM) >> 2) & 0x3) == IND_CODE)
	{
		return (T_IND);
	}
	else if ((((tparams & T_THIRD_PARAM) >> 2) & 0x3) == REG_CODE)
	{
		return (T_REG);
	}
	else if ((((tparams & T_THIRD_PARAM) >> 2) & 0x3) == DIR_CODE)
	{
		return (T_DIR);
	}
	else
	{
		return (0);
	}
}

uint8_t		force_get_param_type(uint8_t tparams, uint8_t param_number)
{
	if (param_number == 1)
	{
		return (get_force_param1_type(tparams));
	}
	else if (param_number == 2)
	{
		return (get_force_param2_type(tparams));
	}
	else
	{
		return (get_force_param3_type(tparams));
	}
}
