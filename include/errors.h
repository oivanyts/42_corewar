#ifndef COREWAR_ERRORS_H
#define COREWAR_ERRORS_H

#include "asm.h"

void	err_lex(t_asm *a);
void	err_no_endline(t_asm *a);
void	err_no_closed_quote(t_asm *a);

#endif