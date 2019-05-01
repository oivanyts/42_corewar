#include "asm.h"

void	add_to_label_list(t_label_list **label_list, char *name, t_asm *a)
{
	t_label_list	*tmp;
	tmp = (t_label_list*)ft_memalloc(sizeof(t_label_list));
	tmp->name = name;
	tmp->op = a->op_list;
	if (*label_list == NULL)
		*label_list = tmp;
	else
	{
		tmp->next = *label_list;
		*label_list = tmp;
	}
}