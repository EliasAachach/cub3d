/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:44:35 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/04 15:45:31 by elaachac         ###   ########.fr       */
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