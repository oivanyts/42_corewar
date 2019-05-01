#include "asm.h"
#define ABS(n) (n) < 0 ? ((n) * -1) : (n)

int 	check_condition(t_asm *a)
{
	int		condition;

	condition = 0;
	while (a->lex_condition[condition](a->fsm->curr) == 0)
		condition++;
	return (condition);
}

void	first_state_init(t_asm *a, t_fsm *fsm)
{
	if (fsm->state == 1)
	{
		fsm->start = fsm->curr;
		fsm->st_col = a->col;
		fsm->st_row = a->row;
	}
}

void	finite_state_machine(t_asm *a, t_fsm *fsm)
{
	int		cond;
	int		id_ret;

	fsm->state = 1;
	while (fsm->state > 0)
	{
		first_state_init(a, fsm);
		cond = check_condition(a);
		fsm->state = fsm->table[fsm->state - 1][cond];
		if (fsm->state <= 0)
		{
			id_ret = a->id_state[ABS(fsm->state)](a);
			fsm->curr += id_ret;
			a->col += id_ret;
			break ;
		}
		if (*fsm->curr == '\n')
		{
			a->col = 1;
			a->row++;
		}
		fsm->curr++;
		a->col++;
		if (*fsm->curr == '\0')
			break ;
	}
}