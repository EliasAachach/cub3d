/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:38:42 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/29 14:06:59 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub3d.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	unsigned int nbr;

	nbr = n;
	if (n < 0)
	{
		ft_putchar('-');
		nbr = -n;
	}
	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	ft_putchar(nbr % 10 + '0');
}


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
		ray->side_distx = (ray->dda.mapx + 1.0 - ray->posx)\
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

void	data_draw(t_ray *ray, t_parsing *parsing)
{
	ray->draw.line_height = (int)(ray->resy / ray->perp_wall_dist);
	ray->draw.start_draw = -ray->draw.line_height / 2 + ray->resy / 2;
	if (ray->draw.start_draw < 0)
		ray->draw.start_draw = 0;
	ray->draw.end_draw = ray->draw.line_height / 2 + ray->resy / 2;
	if (ray->draw.end_draw >= ray->resy)
		ray->draw.end_draw = ray->resy - 1;
	if (parsing->map[ray->dda.mapx][ray->dda.mapy] == 1)
	{
		ray->wall.r = 255;
		ray->wall.g = 0;
		ray->wall.b = 0;
		if (ray->dda.side == 1)
			ray->wall.r = 255 / 2;
	}
	if (parsing->map[ray->dda.mapx][ray->dda.mapy] == 2)
	{
		ray->wall.r = 180;
		ray->wall.g = 180;
		ray->wall.b = 0;
		if (ray->dda.side == 1)
			ray->wall.g = 255 / 2;
	}
	ray->floor.r = 80;
	ray->floor.g = 80;
	ray->floor.b = 80;
	ray->roof.r = 0;
	ray->roof.g = 100;
	ray->roof.b = 0;
}

void	colorpix(int x, int y, t_ray *ray, t_colors color)
{
	int pos;

	pos = (y * ray->resx + x) * 4;
	ray->mlx.data_addr[pos + RGB_B] = color.b;
	ray->mlx.data_addr[pos + RGB_G] = color.g;
	ray->mlx.data_addr[pos + RGB_R] = color.r;
}

void	fill_img(t_ray *ray, int x)
{
	int y;

	y = 0;
	while (y < ray->resy)
	{
		if (y < ray->draw.start_draw)
			colorpix(x, y, ray, ray->roof);
		else if(y >= ray->draw.start_draw && y <= ray->draw.end_draw)
		{
			colorpix(x, y, ray, ray->wall);
		}
		else
			colorpix(x, y, ray, ray->floor);
		y++;
	}
}

void	raycast(t_parsing *parsing, t_elems *elems, t_ray *ray)
{
	int	x;

	x = -1;
	while (++x < ray->resx)
	{
		ray->camerax = 2 * x / ray->resx - 1;
		ray->ray_posx = ray->dirx + ray->planx * ray->camerax;
		ray->ray_posy = ray->diry + ray->plany * ray->camerax;
		ray->dda.mapx = (int)ray->posx;
		ray->dda.mapy = (int)ray->posy;
		ray->delta_distx = fabs(1 / ray->ray_dirx);
		ray->delta_distx = fabs(1 / ray->ray_diry);
		set_step_sidedist(ray);
		dda(ray, parsing);
		data_draw(ray, parsing);
		ray->mlx.data_addr = mlx_get_data_addr(ray->mlx.img_ptr,\
		&(ray->mlx.bpp), &(ray->mlx.size), &(ray->mlx.endian));
		fill_img(ray, x);
	}
}

void	put_window(void *mlx_ptr, void *win_ptr, void *img)
{
	mlx_put_image_to_window(mlx_ptr, win_ptr, img, 0, 0);
}

void	init_var(t_ray *ray)
{
	ray->dirx = 0;
	ray->diry = 0;
	ray->planx = 0;
	ray->plany = 0;
	ray->dda.hit = 0;
}

void    raycasting(t_parsing *parsing, t_elems *elems, t_ray *ray)
{
	ray->posx = (double)parsing->player_x;
	ray->posy = (double)parsing->player_y;
	init_var(ray);
	set_dir_plan(parsing->player_dir, ray);
	ray->mlx_win =\
	mlx_new_window(elems->mlx_ptr, elems->R_x_value, elems->R_y_value, "Cub3d");
	ray->resx = (double)elems->R_x_value;
	ray->resy =  (double)elems->R_y_value;
	ray->mlx.img_ptr =\
	mlx_new_image(elems->mlx_ptr, elems->R_x_value, elems->R_y_value);
	raycast(parsing, elems, ray);
	put_window(elems->mlx_ptr, ray->mlx_win, ray->mlx.img_ptr);
	mlx_loop(elems->mlx_ptr);
}