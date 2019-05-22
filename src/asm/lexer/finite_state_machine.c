/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finite_state_machine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:25:50 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 12:45:51 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "fsm.h"
#define ABS(n) (n) < 0 ? ((n) * -1) : (n)

static int	check_condition(t_asm *a)
{
	int		condition;

	condition = 0;
	while (a->lex_condition[condition](a->fsm->curr) == 0)
		condition++;
	return (condition);
}

static void	first_state_init(t_asm *a, t_fsm *fsm)
{
	if (fsm->state == 1)
	{
		fsm->start = fsm->curr;
		fsm->st_col = a->col;
		fsm->st_row = a->row;
	}
}

static void	check_errors(t_asm *a)
{
	if (a->fsm->state == 0)
		a->errors[0](a);
	else if (a->fsm->state < -100)
	{
		a->fsm->state += 100;
		a->errors[ABS(a->fsm->state)](a);
	}
}

void		finite_state_machine(t_asm *a, t_fsm *fsm)
{
	int		cond;
	int		id_ret;

	fsm->state = 1;
	while (fsm->state > 0)
	{
		first_state_init(a, fsm);
		cond = check_condition(a);
		fsm->state = g_fsm[fsm->state - 1][cond];
		if (fsm->state <= 0)
		{
			check_errors(a);
			id_ret = a->id_state[ABS(fsm->state)](a);
			fsm->curr += id_ret;
			a->col += id_ret;
			break ;
		}
		if (*fsm->curr == '\n')
		{
			a->col = 0;
			a->row++;
		}
		fsm->curr++;
		a->col++;
	}
}
