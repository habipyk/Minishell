
#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	char	*a;
	char	*b;

	a = (char *) dst;
	b = (char *) src;
	if (n == 0 || a == b)
	{
		return (dst);
	}
	while (n--)
	{
		*a = *b;
		a++;
		b++;
	}
	return (dst);
}
