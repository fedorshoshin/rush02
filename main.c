#include "rush02.h"

int	main(int argc, char **argv)
{
	char	*dict;
	char	*path;
	char	*num;

	if (argc != 2 && argc != 3)
		return (1);
	num = argv[argc - 1];
	path = "numbers.dict";
	if (argc == 3)
		path = argv[1];
	if (!valid_number(num))
		return (write(1, "Error\n", 6), 1);
	dict = load_dict(path, count(skip_zeroes(num)));
	if (!dict)
		return (write(1, "Dict Error\n", 11), 1);
	if (skip_zeroes(num)[0] == '0')
		print_val(find_key(dict, "0"));
	else
		construct(dict, num);
	write(1, "\n", 1);
	free(dict);
	return (0);
}
