#include "asm.h"
#include "lexer.h"

int		lex_comment(char *c)
{
	return (str_cmp(c, COMMENT_CMD_STRING));
}

int		lex_whitespace(char *c)
{
	return (*c == ' ' || *c == '\t');
}

int		lex_other(char *c)
{
	return (1);
}