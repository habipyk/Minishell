
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*rtn;
	size_t	len;

	len = ft_strlen(s1) + 1;
	rtn = ft_calloc(len, sizeof(char));
	if (!rtn)
		return (0);
	ft_strlcpy(rtn, s1, len);
	return (rtn);
}
