/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:44:35 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/04 17:37:14 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strndup(char *s1, int len, int i)
{
	int		j;
	char	*s2;

	j = 0;
	s2 = ((char *)malloc(sizeof(char) * (len + 1)));
	if (!s2)
		return (NULL);
	while (s1[i] && j <= len)
	{
		s2[j] = s1[i];
		i++;
		j++;
	}
	s2[j] = '\0';
	return (s2);
}

int		ft_strdup_path2(char *tmp, int elem_flag, t_elems *elems)
{
	if (elem_flag == 'E' + 'A')
	{
		elems->path_to_EA = ft_strdup(tmp);
		if (elems->path_to_EA == NULL)
			return (1);
		return (0);
	}
	if (elem_flag == 'W' + 'E')
	{
		elems->path_to_WE = ft_strdup(tmp);
		if (elems->path_to_WE == NULL)
			return (1);
		return (0);
	}
	return (1);
}

int		ft_strdup_path(char *tmp, int elem_flag, t_elems *elems)
{
	if (elem_flag == 'S')
	{
		elems->path_to_S = ft_strdup(tmp);
		if (elems->path_to_S == NULL)
			return (1);
		return (0);
	}
	if (elem_flag == 'N' + 'O')
	{
		elems->path_to_NO = ft_strdup(tmp);
		if (elems->path_to_NO == NULL)
			return (1);
		return (0);
	}
		if (elem_flag == 'S' + 'O')
		{
			elems->path_to_SO = ft_strdup(tmp);
			if (elems->path_to_SO == NULL)
				return (1);
			return (0);
		}
	return (ft_strdup_path2(tmp, elem_flag, elems));
}

int		existing_path(char *tmp)
{
	int	fd;

	fd = open(tmp, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	get_path(char *newline, int elem_flag, t_elems *elems)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	j = 0;
	i = 2;
	len = 0;
	if (elem_flag == 'S')
		i = 1;
	while ((newline[i] == ' ' || newline[i] == '	') && newline[i])
		i++;
	j = i;
	while (!(newline[j] == ' ' || newline[j] == '	') && newline[j])
	{
		j++;
		len++;
	}
	tmp = ft_strndup(newline, len, i);
	if (ft_strdup_path(tmp, elem_flag, elems) == 1 || existing_path(tmp) == 1)
	{
		free(tmp);
		error_elems(newline, elems, 5);
	}
	free(tmp);
}