#include "libft.h"

int		str_cmp(char *str, char *src)
{
	while (*str != '\0' && *src != '\0' && *src == *str)
	{
		str++;
		src++;
	}
	if (*src == '\0')
		return (1);
	return (0);
}