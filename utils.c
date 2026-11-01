#include "rush02.h"

int	count(char *num)
{
	int	i;

	i = 0;
	while (num[i])
		i++;
	return (i);
}

char	*skip_zeroes(char *num)
{
	while (*num == '0' && *(num + 1))
		num++;
	return (num);
}

int	is_power(char *num)
{
	int	i;

	if (num[0] != '1')
		return (0);
	i = 1;
	while (num[i] == '0')
		i++;
	return (num[i] == '\0');
}

char	*create_power_key(int power)
{
	char	*key;
	int		i;

	key = malloc(power + 2);
	if (!key)
		return (NULL);
	key[0] = '1';
	i = 1;
	while (i <= power)
	{
		key[i] = '0';
		i++;
	}
	key[i] = '\0';
	return (key);
}
