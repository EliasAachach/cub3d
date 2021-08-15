/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:33:19 by user42            #+#    #+#             */
/*   Updated: 2021/08/15 14:24:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_var2(t_ray *ray, t_elems *elems)
{
	ray->wall.r = 0;
	ray->wall.g = 0;
	ray->wall.b = 0;
	ray->mv.w = 0;
	ray->mv.a = 0;
	ray->mv.s = 0;
	ray->mv.d = 0;
	ray->mv.left = 0;
	ray->mv.right = 0;
	ray->mv.speed = 0.05;
	ray->mv.rotspeed = 0.05;
	ray->mlx.img_ptr = NULL;
	ray->mlx.data_addr = NULL;
	ray->mlx.mlx_win = mlx_new_window(ray->mlx.mlx_ptr, \
		elems->R_x_value, elems->R_y_value, "Cub3d");
	ray->mlx.bpp = 0;
	ray->mlx.endian = 0;
	ray->img.endian = 0;
	ray->img.bpp = 0;
	ray->img.s_line = 0;
	ray->img.image = NULL;
	ray->img.addr = NULL;
}

void	init_var(t_ray *ray, t_elems *elems)
{
	ray->dirx = 0;
	ray->diry = 0;
	ray->posx = 0;
	ray->posy = 0;
	ray->planx = 0;
	ray->plany = 0;
	ray->ray_dirx = 0;
	ray->ray_diry = 0;
	ray->side_distx = 0;
	ray->side_disty = 0;
	ray->camerax = 0;
	ray->dda.side = 0;
	ray->dda.hit = 0;
	ray->dda.stepx = 0;
	ray->dda.stepy = 0;
	ray->draw.start_draw = 0;
	ray->draw.end_draw = 0;
	ray->draw.line_height = 0;
	ray->roof.r = elems->r_C;
	ray->roof.g = elems->g_C;
	ray->roof.b = elems->b_C;
	ray->floor.r = elems->r_F;
	ray->floor.g = elems->g_F;
	ray->floor.b = elems->b_F;
	ray->tex.step = 0;
	init_var2(ray, elems);
}
