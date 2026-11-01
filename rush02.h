#ifndef RUSH02_H
# define RUSH02_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

int		get_size(char *path);
char	*cr_str(char *path, int size);
int		count(char *num);
char	*skip_zeroes(char *num);
int		is_power(char *num);
char	*create_power_key(int power);
char	*match_key(char *line, char *key);
char	*find_key(char *dict, char *key);
void	print_val(char *str);
void	print_digit(char *dict, char c);
void	print_tens(char *dict, char *num);
void	print_group(char *dict, char *num);
void	print_power(char *dict, int power);
void	split_print(char *dict, char *num, int len);
void	construct(char *dict, char *num);

#endif
