#include "rush02.h"

void	print_power(char *dict, int power)
{
	char	*power_key;

	power_key = create_power_key(power);
	if (!power_key)
		return ;
	print_val(find_key(dict, power_key));
	free(power_key);
}

void	split_print(char *dict, char *num, int len)
{
	char	prefix[4];
	int		first_len;
	int		i;

	first_len = len % 3;
	if (first_len == 0)
		first_len = 3;
	i = 0;
	while (i < first_len)
	{
		prefix[i] = num[i];
		i++;
	}
	prefix[i] = '\0';
	construct(dict, prefix);
	print_power(dict, len - first_len);
	construct(dict, num + first_len);
}

void	construct(char *dict, char *num)
{
	char	*value;
	int		len;

	num = skip_zeroes(num);
	if (num[0] == '0')
		return ;
	len = count(num);
	value = NULL;
	if (len > 3 && !is_power(num))
		value = find_key(dict, num);
	if (value)
		print_val(value);
	else if (len <= 3)
		print_group(dict, num);
	else
		split_print(dict, num, len);
}
