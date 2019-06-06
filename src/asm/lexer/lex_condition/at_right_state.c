int		at_right_state(char *mas, int len, char curr_state)
{
	while (--len >= 0)
	{
		if (mas[len] == curr_state)
			return (1);
	}
	return (0);
}