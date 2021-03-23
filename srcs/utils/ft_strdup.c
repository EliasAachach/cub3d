#include "cub3d.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	if (!(s2 = ((char *)malloc(sizeof(char) * (ft_strlen(s1) + 1)))))
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
