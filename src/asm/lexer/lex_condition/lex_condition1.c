#include "asm.h"

int		lex_separator_char(char *c)
{
	return (*c == SEPARATOR_CHAR);
}

int		lex_label_char(char *c)
{
	return (*c == LABEL_CHAR);
}

int		lex_comment_endline(char *c)
{
	return (*c == COMMENT_CHAR || *c == ALT_COMMENT_CHAR || *c == '\n');
}

int		lex_quote(char *c)
{
	return (*c == '"');
}

int 	lex_name(char *c)
{
	return (ft_strcmp(NAME_CMD_STRING, c) == 0);
}