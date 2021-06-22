/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:38:42 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/22 18:37:02 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir_plan(int player_dir, t_ray *ray)
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

void	raycast(t_parsing *parsing, t_elems *elems, t_ray *ray)
{
	int	x;

	x = 0;
	while (x < ray->resx && x++)
	{
		ray->camerax = 2 * x / ray->resx - 1;
		ray->ray_dirx = ray->dirx + ray->planx * ray->camerax;
		ray->ray_diry = ray->diry + ray->plany * ray->camerax;
		ray->dda->mapx = (int)ray->posx
		ray->dda->mapy = (int)ray->posy
	}
}

void    raycasting(t_parsing *parsing, t_elems *elems, t_ray *ray)
{
	ray->posx = (double)parsing->player_x;
	ray->posy = (double)parsing->player_y;
	set_dir_plan(parsing->player_dir, ray);
	ray->mlx_win =\
	mlx_new_window(elems->mlx_ptr, elems->R_x_value, elems->R_y_value, "Cub3d");
	ray->resx = elems->R_x_value;
	//RAYCASTING STARTS HERE
	raycast(parsing, elems, ray);
	mlx_loop(elems->mlx_ptr);
}