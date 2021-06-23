/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:38:42 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/23 19:12:59 by elaachac         ###   ########.fr       */
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

void	set_step_sidedist(t_ray *ray)
{
	if (ray->ray_dirx < 0)
	{
		ray->dda.stepx = -1;
		ray->side_distx = (ray->posx - ray->dda.mapx) * ray->delta_distx;
	}
	else
	{
		ray->dda.stepx = -1;
		ray->side_distx = (ray->dda.mapx + 1.0 - ray->posx)\
		* ray->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		ray->dda.stepy = -1;
		ray->side_disty = (ray->posy - ray->dda.mapy) *ray->delta_disty;
	}
	else
	{
		ray->dda.stepy = 1;
		ray->side_disty = (ray->dda.mapy + 1.0 - ray->posy) * ray->delta_disty;
	}
}

void	dda(t_ray *ray, t_parsing *parsing)
{
	while (ray->dda.hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->dda.mapx += ray->dda.stepx;
			ray->dda.side = X_WALL;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->dda.mapy += ray->dda.stepy;
			ray->dda.side = Y_WALL;
		}
		if (parsing->map[ray->dda.mapx][ray->dda.mapy] > 0)
			ray->dda.hit = 1;
	}
	if (ray->dda.side == 0)
		ray->perp_wall_dist = (ray->dda.mapx - ray->posx +\
		(1 - ray->dda.stepx) / 2) / ray->ray_dirx;
	else
		ray->perp_wall_dist = (ray->dda.mapy - ray->posy +\
		(1 - ray->dda.stepy) / 2) / ray->ray_diry;
}

void	data_draw(t_ray *ray)
{
	ray->draw.line_height = (int)(ray->resy / ray->perp_wall_dist);
	ray->draw.start_draw = -ray->draw.line_height / 2 + ray->resy / 2;
	if (ray->draw.start_draw < 0)
		ray->draw.start_draw = 0;
	ray->draw.end_draw = ray->draw.line_height / 2 + ray->resy / 2;
	if (ray->draw.end_draw >= ray->resy)
		ray->draw.end_draw = ray->resy - 1;
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
		ray->dda.mapx = (int)ray->posx;
		ray->dda.mapy = (int)ray->posy;
		ray->delta_distx = abs(1 / ray->ray_dirx);
		ray->delta_distx = abs(1 / ray->ray_diry);
		set_step_sidedist(ray);
		dda(ray, parsing);
		data_draw(ray);
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
	ray->resy = elems->R_y_value;
	//RAYCASTING STARTS HERE
	raycast(parsing, elems, ray);
	mlx_loop(elems->mlx_ptr);
}