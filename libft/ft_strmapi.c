
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*rtn;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	rtn = (char *)malloc(len * sizeof(char) + 1);
	if (!rtn)
		return (0);
	while (i < len)
	{
		rtn[i] = (*f)(i, s[i]);
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
