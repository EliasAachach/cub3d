/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:38:42 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/21 16:30:15 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir(int player_dir, t_ray *ray)
{
	if (player_dir == 'N')
	{
		ray->dirx = -1;
		ray->plany = 0.66;
	}
	if (player_dir == 'S')
	{
		ray->dirx = 1;
		ray->plany = -0.66;
	}
	if (player_dir == 'W')
	{
		ray->diry = -1;
		ray->planx = -0.66;
	}
	if (player_dir == 'E')
	{
		ray->diry = 1;
		ray->planx = 0.66;
	}
}

void    raycast(t_parsing *parsing, t_elems *elems, t_ray *ray)
{
	ray->posx = (double)parsing->player_x;
	ray->posy = (double)parsing->player_y;
	set_dir_plan(parsing->player_dir, ray);
	ray->mlx_win =\
	mlx_new_window(elems->mlx_ptr, elems->R_x_value, elems->R_y_value, "Cub3d");
}