#ifndef LEXER_H
#define LEXER_H

char	*read_text_from(char *name); //Don't check '\n' at EOF
void		read_table(char *name, t_fsm *fsm);

#endif