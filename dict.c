#include "rush02.h"

char	*match_key(char *line, char *key)
{
	int	j;

	j = 0;
	while (key[j] && line[j] == key[j])
		j++;
	if (key[j] != '\0')
		return (NULL);
	while (line[j] == ' ')
		j++;
	if (line[j] != ':')
		return (NULL);
	j++;
	while (line[j] == ' ')
		j++;
	return (line + j);
}

char	*find_key(char *dict, char *key)
{
	int		i;
	char	*value;

	i = 0;
	while (dict[i])
	{
		if (i == 0 || dict[i - 1] == '\n')
		{
			value = match_key(dict + i, key);
			if (value)
				return (value);
		}
		i++;
	}
	return (NULL);
}

void	print_val(char *str)
{
	static int	started;
	int			len;

	if (!str)
		return ;
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\r'))
		len--;
	if (started)
		write(1, " ", 1);
	started = 1;
	write(1, str, len);
}
