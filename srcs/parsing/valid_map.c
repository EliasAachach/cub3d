/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 23:21:49 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/05 19:12:15 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_in_map(char c, t_parsing *parsing)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		parsing->player_in_map = TRUE;
		return (1);
	}
	else
		return (0);
}

void	get_valid_map(t_parsing *parsing, char **ff_map)
{
	int		i;

	i = 0;
	while (i < parsing->nbr_lines)
	{
		ff_map[i] = ft_strdup(parsing->map[i]);
		i++;
	}
}

void	player_here(t_parsing *parsing, int x, int y, char **ff_map)
{
	parsing->player_x = x;
	parsing->player_y = y;
	ff_map[x][y] = '0';
	flood_fill(parsing, ff_map, x, y);
	ft_strfree(ff_map);
}

void	valid_map(t_parsing *parsing)
{
	int		x;
	int		y;
	char	**ff_map;

	x = 0;
	ff_map = alloc_map(parsing->nbr_lines, parsing->longest_line);
	get_valid_map(parsing, ff_map);
	while (x < parsing->nbr_lines)
	{
		y = 0;
		while (ff_map[x][y])
		{
			if (player_in_map(ff_map[x][y], parsing) == 1)
			{
				player_here(parsing, x, y, ff_map);
				return ;
			}
			y++;
		}
		x++;
	}
	ft_strfree(ff_map);
}
