/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:37:16 by user42            #+#    #+#             */
/*   Updated: 2021/08/08 19:37:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ff_check(t_parsing *parsing, char **ff_map, int x, int y)
{
	if (player_in_map(ff_map[x][y], parsing) == 1)
		parsing->map_is_open = TRUE;
	if (x == 0 && ff_map[x][y] != '1')
		parsing->map_is_open = TRUE;
	if (y == 0 && ff_map[x][y] != '1')
		parsing->map_is_open = TRUE;
	if (x == parsing->nbr_lines && ff_map[x][y] != '1')
		parsing->map_is_open = TRUE;
	if (y == parsing->longest_line && ff_map[x][y] != '1')
		parsing->map_is_open = TRUE;
	if (ff_map[x][y] == '1')
		ff_map[x][y] = -2;
}

int	check_sides(char side)
{
	if (side == '0')
		return (0);
	if (side == '1')
		return (0);
	if (side == '2')
		return (0);
	if (side == ' ')
		return (0);
	if (side == -1)
		return (0);
	if (side == -2)
		return (0);
	if (side == -3)
		return (0);
	return (1);
}

int	check_adjacent_cases(t_parsing *parsing, char **ff_map, int x, int y)
{
	if (x - 1 < 0 || check_sides(ff_map[x - 1][y]) == 1)
		return (1);
	if (check_sides(ff_map[x][y + 1]) == 1)
		return (1);
	if (x + 1 >= parsing->nbr_lines || check_sides(ff_map[x + 1][y]) == 1)
		return (1);
	if (check_sides(ff_map[x][y - 1]) == 1)
		return (1);
	return (0);
}

void	flood_fill(t_parsing *parsing, char **ff_map, int x, int y)
{
	if (ff_map[x][y] != '1' && ff_map[x][y] != -2)
	{
		if (check_adjacent_cases(parsing, ff_map, x, y) == 1)
		{
			parsing->map_is_open = TRUE;
			return ;
		}
	}
	ff_check(parsing, ff_map, x, y);
	if (ff_map[x][y] == '0' || ff_map[x][y] == '2'
		|| ff_map[x][y] == ' ')
	{
		if (ff_map[x][y] == '2')
			ff_map[x][y] = -3;
		else
			ff_map[x][y] = -1;
		flood_fill(parsing, ff_map, x, y + 1);
		flood_fill(parsing, ff_map, x, y - 1);
		flood_fill(parsing, ff_map, x + 1, y);
		flood_fill(parsing, ff_map, x - 1, y);
	}
}
