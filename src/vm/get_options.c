#include "libft.h"

char	*is_param(char *string, const char *options)
{
	char	*ret;
	if (*string++ != '-' || !*string)
		return (NULL);
	if ((ret = ft_strchr(options, *string)))
		return (ret);
	return (NULL);
}

int get_options(int	argc, char *argv[], const char *options)
{
	uint8_t n_op;
	uint8_t i = 1;

	n_op = 0;
	while (i <= argc)
	{
		if (is_param(argv[i], options))
		{

		}
		else
		{

		}
		i++;
	}
	return (2);
}