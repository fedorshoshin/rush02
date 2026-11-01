#include "rush02.h"

void	print_digit(char *dict, char c)
{
	char	digit[2];

	digit[0] = c;
	digit[1] = '\0';
	print_val(find_key(dict, digit));
}

void	print_tens(char *dict, char *num)
{
	char	key[3];
	char	*value;

	key[0] = num[0];
	key[1] = num[1];
	key[2] = '\0';
	value = find_key(dict, key);
	if (value)
	{
		print_val(value);
		return ;
	}
	key[1] = '0';
	print_val(find_key(dict, key));
	if (num[1] != '0')
		print_digit(dict, num[1]);
}

void	print_group(char *dict, char *num)
{
	char	*value;
	int		len;

	num = skip_zeroes(num);
	if (num[0] == '0')
		return ;
	len = count(num);
	value = NULL;
	if (!is_power(num))
		value = find_key(dict, num);
	if (value)
	{
		print_val(value);
		return ;
	}
	if (len == 3)
	{
		print_digit(dict, num[0]);
		print_val(find_key(dict, "100"));
	}
	if (len >= 2 && num[len - 2] != '0')
		print_tens(dict, num + len - 2);
	else if (num[len - 1] != '0')
		print_digit(dict, num[len - 1]);
}
