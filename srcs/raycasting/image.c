/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:29:32 by user42            #+#    #+#             */
/*   Updated: 2021/08/15 14:22:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	colorpix(int x, int y, t_ray *ray, t_colors color)
{
	int	pos;

	pos = (y * ray->resx + x) * 4;
	ray->mlx.data_addr[pos + RGB_B] = color.b;
	ray->mlx.data_addr[pos + RGB_G] = color.g;
	ray->mlx.data_addr[pos + RGB_R] = color.r;
}

void	fill_img(t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->resy)
	{
		if (y < ray->draw.start_draw && ray->draw.start_draw)
			colorpix(x, y, ray, ray->roof);
		else if (y >= ray->draw.start_draw && y <= ray->draw.end_draw)
		{
			ray->tex.step = (1.0 * TEXHEIGHT) / ray->draw.line_height;
			ray->tex.y = (int)ray->tex.pos & (TEXHEIGHT - 1);
			ray->tex.pos += ray->tex.step;
			ray->wall.r = ray->img.image[ray->tex.num] \
				[(TEXHEIGHT * ray->tex.y + ray->tex.x) *4 + RGB_R];
			ray->wall.g = ray->img.image[ray->tex.num] \
				[(TEXHEIGHT * ray->tex.y + ray->tex.x) *4 + RGB_G];
			ray->wall.b = ray->img.image[ray->tex.num] \
				[(TEXHEIGHT * ray->tex.y + ray->tex.x) *4 + RGB_B];
			colorpix(x, y, ray, ray->wall);
		}
		else
			colorpix(x, y, ray, ray->floor);
		y++;
	}
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
	if (ray->dda.side == 0)
		ray->tex.wallx = ray->posy + ray->perp_wall_dist * ray->ray_diry;
	else
		ray->tex.wallx = ray->posx + ray->perp_wall_dist * ray->ray_dirx;
	ray->tex.wallx -= floor(ray->tex.wallx);
	ray->tex.x = (int)(ray->tex.wallx * (double)TEXWIDTH);
	ray->tex.pos = (ray->draw.start_draw - ray->resy / 2 + \
		ray->draw.line_height / 2) * ray->tex.step;
	if (ray->dda.side == 0 && ray->ray_dirx > 0)
		ray->tex.x = TEXWIDTH - ray->tex.x - 1;
	if (ray->dda.side == 1 && ray->ray_diry < 0)
		ray->tex.x = TEXWIDTH - ray->tex.x - 1;
	ray->tex.step = (1.0 * TEXHEIGHT) / ray->draw.line_height;
}

void	init_image(t_ray *ray)
{
	if (ray->mlx.img_ptr && ray->mlx.mlx_ptr)
	{
		mlx_destroy_image(ray->mlx.mlx_ptr, ray->mlx.img_ptr);
	}
	ray->mlx.img_ptr = mlx_new_image(ray->mlx.mlx_ptr, ray->mlx.x, ray->mlx.y);
	ray->mlx.data_addr = mlx_get_data_addr(ray->mlx.img_ptr, \
		&(ray->mlx.bpp), &(ray->mlx.size), &(ray->mlx.endian));
}

void	put_window(void *mlx_ptr, void *win_ptr, void *img)
{
	mlx_put_image_to_window(mlx_ptr, win_ptr, img, 0, 0);
}
