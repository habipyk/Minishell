
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!ft_strlen(needle))
		return ((char *)haystack);
	i = 0;
	while (i < len && *(haystack + i))
	{
		j = 0;
		while ((i + j) < len && *(haystack + i + j) == *(needle + j))
		{
			if (!*(needle + j + 1))
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
