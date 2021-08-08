/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:41:52 by user42            #+#    #+#             */
/*   Updated: 2021/08/08 18:48:48 by user42           ###   ########.fr       */
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
		ray->dda.stepx = 1;
		ray->side_distx = (ray->dda.mapx + 1.0 - ray->posx) \
		* ray->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		ray->dda.stepy = -1;
		ray->side_disty = (ray->posy - ray->dda.mapy) * ray->delta_disty;
	}
	else
	{
		ray->dda.stepy = 1;
		ray->side_disty = (ray->dda.mapy + 1.0 - ray->posy) * ray->delta_disty;
	}
}

void	dda2(t_ray *ray)
{
	if (ray->tex.num == 0 && ray->posx > ray->dda.mapx)
		ray->tex.num = 2;
	else if (ray->tex.num && ray->posy > ray->dda.mapy)
		ray->tex.num = 3;
	if (ray->dda.side == X_WALL)
		ray->perp_wall_dist = (ray->dda.mapx - ray->posx + \
		(1 - ray->dda.stepx) / 2) / ray->ray_dirx;
	else
		ray->perp_wall_dist = (ray->dda.mapy - ray->posy + \
		(1 - ray->dda.stepy) / 2) / ray->ray_diry;
}

void	dda(t_ray *ray)
{
	ray->dda.hit = 0;
	while (ray->dda.hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->dda.mapx += ray->dda.stepx;
			ray->dda.side = X_WALL;
			ray->tex.num = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->dda.mapy += ray->dda.stepy;
			ray->dda.side = Y_WALL;
			ray->tex.num = 1;
		}
		if (ray->map[ray->dda.mapx][ray->dda.mapy] == '1')
			ray->dda.hit = 1;
	}
	dda2(ray);
}
