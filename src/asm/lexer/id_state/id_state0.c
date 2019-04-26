#include "asm.h"
#include "lexer.h"

int		id_error(t_asm *a)
{
	ft_printf("Lexical error at [%i:%i]", a->row, a->col);
	exit(1);
}

int		id_indirect(t_asm *a)
{
	t_fsm	*fsm;
	char	*data;
	int		*i;
	size_t	len;

	fsm = a->fsm;
	len = fsm->curr - fsm->start;
	data = (char*)ft_memalloc(len + 1);
	ft_strncpy(data, fsm->start, len);
	i = (int*)malloc(sizeof(int));
	*i = ft_atoi(data);
	free(data);
	add_to_token_list(&a->token_list, INDIRECT, i, a);
	return (0);
}

int		id_label(t_asm *a)
{
	t_fsm	*fsm;
	char	*data;
	size_t 	len;

	fsm = a->fsm;
	len = fsm->curr - fsm->start;
	data = (char*)ft_memalloc(len + 1);
	ft_strncpy(data, fsm->start, len);
	add_to_token_list(&a->token_list, LABEL, data, a);
	return (1);
}

int		id_instruction(t_asm *a)
{
	t_fsm	*fsm;
	char	*data;
	size_t 	len;

	fsm = a->fsm;
	len = fsm->curr - fsm->start;
	data = (char*)ft_memalloc(len + 1);
	ft_strncpy(data, fsm->start, len);
	add_to_token_list(&a->token_list, INSTRUCTION, data, a);
	return (0);
}

int		id_register(t_asm *a)
{
	t_fsm	*fsm;
	char	*data;
	int		*i;
	size_t	len;

	fsm = a->fsm;
	len = fsm->curr - fsm->start + 1;
	data = (char*)ft_memalloc(len + 1);
	ft_strncpy(data, fsm->start + 1, len);
	i = (int*)malloc(sizeof(int));
	*i = ft_atoi(data);
	free(data);
	add_to_token_list(&a->token_list, REGISTER, i, a);
	return (0);
}