#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	get_size(char *path)
{
	int		fd;
	int		total;
	int		b_read;
	char	buf[1024];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	total = 0;
	while (1)
	{
		b_read = read(fd, buf, 1024);
		if (b_read < 0)
			return (close(fd), -1);
		if (b_read == 0)
			break ;
		total += b_read;
	}
	close(fd);
	return (total);
}

char	*cr_str(char *path, int size)
{
	char	*buf;
	int		fd;
	int		total;
	int		b_read;

	buf = malloc(size + 1);
	if (!buf)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(buf), NULL);
	total = 0;
	while (total < size)
	{
		b_read = read(fd, buf + total, size - total);
		if (b_read <= 0)
			return (close(fd), free(buf), NULL);
		total += b_read;
	}
	buf[size] = '\0';
	close(fd);
	return (buf);
}

int	count(char *num)
{
	int	i;

	i = 0;
	while (num[i])
		i++;
	return (i);
}

char	*find_key(char *dict, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (dict[i])
	{
		if (i == 0 || dict[i - 1] == '\n')
		{
			j = 0;
			while (key[j] && dict[i + j] == key[j])
				j++;
			if (key[j] == '\0')
			{
				while (dict[i + j] == ' ')
					j++;
				if (dict[i + j] == ':')
				{
					j++;
					while (dict[i + j] == ' ')
						j++;
					return (dict + i + j);
				}
			}
		}
		i++;
	}
	return (NULL);
}

void	print_val(char *str)
{
	if (!str)
		return ;
	while (*str && *str != '\n')
	{
		if (*str >= 33 && *str <= 126)
			write(1, str, 1);
		str++;
	}
	write(1, " ", 1);
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

char	*skip_zeroes(char *num)
{
	while (*num == '0' && *(num + 1))
		num++;
	return (num);
}

void	print_group(char *dict, char *num)
{
	char	digit[2];
	char	*key;
	char	*value;
	int		len;

	num = skip_zeroes(num);
	if (num[0] == '0')
		return ;
	len = count(num);
	if (!(len == 3 && num[0] == '1'
			&& num[1] == '0' && num[2] == '0'))
	{
		value = find_key(dict, num);
		if (value)
		{
			print_val(value);
			return ;
		}
	}
	if (len == 3 && num[0] != '0')
	{
		digit[0] = num[0];
		digit[1] = '\0';
		print_val(find_key(dict, digit));
		print_val(find_key(dict, "100"));
	}
	if (len >= 2 && num[len - 2] != '0')
	{
		if (num[len - 2] == '1')
		{
			key = malloc(3);
			if (!key)
				return ;
			key[0] = num[len - 2];
			key[1] = num[len - 1];
			key[2] = '\0';
			print_val(find_key(dict, key));
			free(key);
			return ;
		}
		key = malloc(3);
		if (!key)
			return ;
		key[0] = num[len - 2];
		key[1] = '0';
		key[2] = '\0';
		print_val(find_key(dict, key));
		free(key);
	}
	if (num[len - 1] != '0')
	{
		digit[0] = num[len - 1];
		digit[1] = '\0';
		print_val(find_key(dict, digit));
	}
}

void	construct(char *dict, char *num)
{
	int		len;
	int		first_len;
	char	*prefix;
	char	*group;
	char	*power_key;
	char	*value;

	num = skip_zeroes(num);
	if (num[0] == '0')
		return ;
	len = count(num);
	if (len > 3)
	{
		value = find_key(dict, num);
		if (value)
		{
			print_val(value);
			return ;
		}
	}
	if (len <= 3)
	{
		print_group(dict, num);
		return ;
	}
	first_len = len % 3;
	if (first_len == 0)
		first_len = 3;
	prefix = malloc(first_len + 1);
	if (!prefix)
		return ;
	len = 0;
	while (len < first_len)
	{
		prefix[len] = num[len];
		len++;
	}
	prefix[first_len] = '\0';
	group = num + first_len;
	construct(dict, prefix);
	power_key = create_power_key(count(group));
	if (power_key)
	{
		print_val(find_key(dict, power_key));
		free(power_key);
	}
	construct(dict, group);
	free(prefix);
}

int	main(int argc, char **argv)
{
	char	*dict;
	int		size;

	if (argc != 3)
		return (1);
	size = get_size(argv[1]);
	if (size < 0)
		return (1);
	dict = cr_str(argv[1], size);
	if (!dict)
		return (1);
	if (skip_zeroes(argv[2])[0] == '0')
		print_val(find_key(dict, "0"));
	else
		construct(dict, argv[2]);
	free(dict);
	return (0);
}