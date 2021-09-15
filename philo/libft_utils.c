int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			znak;
	long int	digit;

	znak = 1;
	digit = 0;
	while (((*str == ' ' || *str == '\n' || *str == '\v' || *str == '\f' \
		|| *str == '\r' || *str == '\t')) && *str != '\0')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			znak = -1;
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str))
	{
		digit = (digit * 10) + (*str - '0');
		str++;
	}
	return (znak * digit);
}
