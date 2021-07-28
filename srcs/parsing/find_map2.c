/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 18:03:15 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/04 18:10:34 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_first_line(char *line)
{
	int	i;

	i = 0;
	while (ft_strlen(line) > 0 && line[i])
	{
		if (line[i] == ' ' || line[i] == '	')
		{
			i++;
		}
		else
			return (1);
	}
	return (0);
}

int	check_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (1);
		i++;
	}
	return (0);
}
