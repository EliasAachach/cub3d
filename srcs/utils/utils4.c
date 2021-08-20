/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:41:30 by elaachac          #+#    #+#             */
/*   Updated: 2021/08/18 19:34:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	res_check(char *str, t_elems *elems, t_ray *ray)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	mlx_get_screen_size(ray->mlx.mlx_ptr, (&x), (&y));
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	if (elems->R_x_value <= 0 || elems->R_y_value <= 0
		|| elems->R_x_value != elems->x_atoul
		|| elems->R_y_value != elems->y_atoul)
		return (1);
	if (elems->R_x_value > x)
		elems->R_x_value = x;
	if (elems->R_y_value > y)
		elems->R_y_value = y;
	return (0);
}

char	*del_spaces(char *line)
{
	int		i;
	char	*newline;

	i = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	newline = ft_strdup(line + i);
	if (!newline)
		return (NULL);
	return (newline);
}

char	**alloc_map(int nbr_lines, int longest_line)
{
	int		i;
	char	**map;

	i = 0;
	map = ((char **)malloc(sizeof(char *) * (nbr_lines + 1)));
	map[nbr_lines] = NULL;
	if (!map)
		return (NULL);
	return (map);
}

int	rgb_check(t_elems *elems)
{
	if (!(elems->r_F >= 0 && elems->r_F <= 255))
		return (1);
	if (!(elems->g_F >= 0 && elems->g_F <= 255))
		return (1);
	if (!(elems->b_F >= 0 && elems->b_F <= 255))
		return (1);
	if (!(elems->r_C >= 0 && elems->r_C <= 255))
		return (1);
	if (!(elems->g_C >= 0 && elems->g_C <= 255))
		return (1);
	if (!(elems->b_C >= 0 && elems->b_C <= 255))
		return (1);
	return (0);
}
