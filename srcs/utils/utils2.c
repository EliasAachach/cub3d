/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:13:58 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/09 14:37:43 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub3d.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	len = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	len = ft_strlen(&s1[start]);
	if (len != 0)
		while (s1[start + len - 1]
			&& ft_strchr(set, s1[start + len - 1]) != NULL)
			len--;
	return (ft_substr(s1, start, len));
}

int	ft_nbwrds(char const *s, char c)
{
	int	i;
	int	j;

	if (!s)
		return (-1);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (j);
}

static int	w(char const *s, int i, char c)
{
	while (s[i] != c && s[i])
		i++;
	return (i + 1);
}

void	init(int i[3])
{
	i[0] = 0;
	i[1] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		i[3];

	out = (char **)malloc(sizeof(char *) * (ft_nbwrds(s, c) + 1));
	if ((ft_nbwrds(s, c) == -1) || !out)
		return (NULL);
	init(i);
	while (s[i[0]])
	{
		if (s[i[0]] != c)
		{
			out[i[1]] = (char *)malloc(sizeof(char) * w(s, i[0], c));
			if (!out)
				return (ft_strfree(out));
			i[2] = 0;
			while (s[i[0]] != c && s[i[0]])
				out[i[1]][i[2]++] = s[i[0]++];
			out[i[1]][i[2]] = '\0';
			i[1]++;
		}
		else
			i[0]++;
	}
	out[i[1]] = NULL;
	return (out);
}
