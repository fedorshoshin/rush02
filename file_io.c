#include "rush02.h"

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

char	*load_dict(char *path, int len)
{
	char	*dict;
	int		size;

	size = get_size(path);
	if (size < 0)
		return (NULL);
	dict = cr_str(path, size);
	if (!dict)
		return (NULL);
	if (count(dict) != size || !valid_format(dict)
		|| !valid_keys(dict, len))
	{
		free(dict);
		return (NULL);
	}
	return (dict);
}
