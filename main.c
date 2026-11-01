#include "rush02.h"

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