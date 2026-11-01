#include "rush02.h"

int	has_key(char *dict, char a, char b)
{
	char	key[3];

	key[0] = a;
	key[1] = b;
	key[2] = '\0';
	return (find_key(dict, key) != NULL);
}

int	has_power(char *dict, int power)
{
	char	*key;
	int		found;

	key = create_power_key(power);
	if (!key)
		return (0);
	found = (find_key(dict, key) != NULL);
	free(key);
	return (found);
}

int	valid_keys(char *dict, int len)
{
	char	c;
	int		power;

	c = '0';
	while (c <= '9')
	{
		if (!has_key(dict, c, '\0') || !has_key(dict, '1', c))
			return (0);
		if (c >= '2' && !has_key(dict, c, '0'))
			return (0);
		c++;
	}
	if (!has_power(dict, 2))
		return (0);
	power = 3;
	while (power <= 36 || power < len)
	{
		if (!has_power(dict, power))
			return (0);
		power += 3;
	}
	return (1);
}
