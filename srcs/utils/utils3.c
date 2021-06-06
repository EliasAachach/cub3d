/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:22:58 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/06 19:40:12 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub3d.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_strfree(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0)
	{
		i--;
		free(str[i]);
	}
	free(str);
	return ((void *)0);
}

char	*ft_strtrim_inside(char *str)
{
	char	*strnew;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strnew = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!strnew)
	{
		free(str);
		return (NULL);
	}
	ft_bzero(strnew, ft_strlen(str));
	while (str[j])
	{
		if (str[j] != ' ' && str[j] != '	')
		{
			strnew[i] = str[j];
			i++;
		}
		j++;
	}
	strnew[i] = '\0';
	free(str);
	return (strnew);
}

int	check_next_char(char *line)
{
	if (line[0] == 'S' || line[0] == 'N')
	{
		if (line[1] == 'O')
		{
			if (line[0] == 'S')
				return ('S' + 'O');
			else
				return ('N' + 'O');
		}
		else if (line[0] == 'S')
			return ('S');
	}
	else if (line[0] == 'W')
	{
		if (line[1] == 'E')
			return ('W' + 'E');
		else
			return (0);
	}
	else if (line[0] == 'E')
	{
		if (line[1] == 'A')
			return ('E' + 'A');
	}
	return (0);
}
