
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*u;

	u = (unsigned char *)b;
	while (len--)
	{
		*u++ = (unsigned char)c;
	}
	return (b);
}
