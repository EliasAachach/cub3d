#include "../parsing/cub3d.h"

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = ((char *)malloc(sizeof(char) * (ft_strlen(s1) + 1)));
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	wich_elem(char *line, t_elems *elems)
{
	char	*charset;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	charset = "RNSWEFC";
	while (charset[i])
	{
		if (line[0] == charset[i])
		{
			ret = charset[i];
			if (!(charset[i] == 'R' || charset[i] == 'F' || charset[i] == 'C'))
			{
				ret = check_next_char(line);
				if (ret == 0)
					error_elems(line, elems, 0);
			}
			return (ret);
		}
		i++;
	}
	error_elems(line, elems, 0);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	nb;

	i = 0;
	nb = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * neg);
}
