#include "libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || ('\x09' <= c && c <= '\x0D'))
		return (1);
	return (0);
}
