
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*c;

	c = (char *)s;
	while (n--)
	{
		*c++ = 0;
	}
}
