#ifndef LEXER_H
#define LEXER_H

char	*read_text_from(char *name); //Don't check '\n' at EOF
void		read_table(char *name, t_fsm *fsm);

void	add_to_op_list(t_op_list **op_list, t_token_list *token_list);
void	add_to_token_list(t_token_list **token_list, t_identifier ident,
						  void *data, t_asm *a);
void	reverse_op_list(t_op_list **op_list);
void	reverse_token_list(t_token_list **token_list);

void	init_asm(t_asm *a, char *file_name);
void	finite_state_machine(t_asm *a, t_fsm *fsm);
void	lexer(t_asm *a);
int		str_cmp(char *str, char *src);

t_op_list	*get_op_list(char *file_name);
void		print_identifiers(t_op_list *op_list);
void	del_2d_masint(int **mas, t_fsm *fsm);

#endif