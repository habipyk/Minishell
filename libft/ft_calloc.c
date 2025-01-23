
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*rtn;
	size_t	req;

	req = count * size;
	rtn = malloc(req);
	if (!rtn)
		return (0);
	ft_bzero(rtn, req);
	return (rtn);
}
