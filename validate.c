#include "rush02.h"

int	valid_number(char *num)
{
	int	i;

	i = 0;
	while (num[i] >= '0' && num[i] <= '9')
		i++;
	return (i > 0 && num[i] == '\0');
}

int	line_len(char *line)
{
	int	i;
	int	visible;

	i = 0;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (i == 0)
		return (-1);
	while (line[i] == ' ')
		i++;
	if (line[i] != ':')
		return (-1);
	i++;
	visible = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] >= 33 && line[i] <= 126)
			visible = 1;
		i++;
	}
	if (!visible)
		return (-1);
	return (i);
}

int	valid_format(char *dict)
{
	int	i;
	int	len;

	i = 0;
	while (dict[i])
	{
		if (dict[i] == '\r' && dict[i + 1] == '\n')
			i++;
		if (dict[i] != '\n')
		{
			len = line_len(dict + i);
			if (len < 0)
				return (0);
			i += len;
		}
		if (dict[i])
			i++;
	}
	return (1);
}
