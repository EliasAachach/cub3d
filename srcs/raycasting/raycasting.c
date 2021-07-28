/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:38:42 by elaachac          #+#    #+#             */
/*   Updated: 2021/07/22 16:26:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->dda.mapy += ray->dda.stepy;
			ray->dda.side = Y_WALL;
		}
		if (ray->map[ray->dda.mapx][ray->dda.mapy] == '1')
			ray->dda.hit = 1;
	}
	if (ray->dda.side == X_WALL)
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
	if (ray->dda.side == 1)
		ray->wall.r = 255 / 2;
	else
		ray->wall.r = 255;
	if (ray->map[ray->dda.mapx + (int)ray->dda.stepx][ray->dda.mapy +\
		(int)ray->dda.stepy] == '2')
	{
		ray->wall.r = 180;
		ray->wall.g = 180;
		ray->wall.b = 0;
		if (ray->dda.side == 1)
			ray->wall.g = 255 / 2;
	}
	// ray->roof.r = 0;
	// ray->roof.g = 100;
	// ray->roof.b = 150;
	// ray->floor.r = 0;
	// ray->floor.g = 100;
	// ray->floor.b = 0;
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
		if (y < ray->draw.start_draw && ray->draw.start_draw)
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

void	raycast(t_ray *ray)
{
	int	x;

	x = -1;
	while (++x < ray->resx)
	{
		ray->camerax = 2 * x / ray->resx - 1;
		ray->ray_dirx = ray->dirx + ray->planx * ray->camerax;
		ray->ray_diry = ray->diry + ray->plany * ray->camerax;
		ray->dda.mapx = (int)ray->posx;
		ray->dda.mapy = (int)ray->posy;
		ray->delta_distx = fabs(1 / ray->ray_dirx);
		ray->delta_disty = fabs(1 / ray->ray_diry);
		set_step_sidedist(ray);
		dda(ray);
		data_draw(ray);
		fill_img(ray, x);
	}
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
	ray->wall.r = 255;
	ray->wall.g = 0;
	ray->wall.b = 0;
	ray->mv.w = 0;
	ray->mv.a = 0;
	ray->mv.s = 0;
	ray->mv.d = 0;
	ray->mv.left = 0;
	ray->mv.right = 0;
	ray->mv.speed = 0.05;
	ray->mlx.img_ptr = NULL;
	ray->mlx.data_addr = NULL;
	ray->mlx.mlx_win = mlx_new_window(ray->mlx.mlx_ptr,\
		elems->R_x_value, elems->R_y_value, "Cub3d");
}

int            win_close(t_ray *ray)
{
	if (ray->mlx.img_ptr)
		mlx_destroy_image(ray->mlx.mlx_ptr, ray->mlx.img_ptr);
	if (ray->mlx.mlx_ptr && ray->mlx.mlx_win)
		mlx_destroy_window(ray->mlx.mlx_ptr, ray->mlx.mlx_win);
	// mlx_clear_window(ray->mlx.mlx_ptr, ray->mlx.mlx_win);
	exit(0);
	return (0);
}

void	init_image(t_ray *ray)
{
	if (ray->mlx.img_ptr && ray->mlx.mlx_ptr)
	{
		mlx_destroy_image(ray->mlx.mlx_ptr, ray->mlx.img_ptr);
	}
	ray->mlx.img_ptr = mlx_new_image(ray->mlx.mlx_ptr, ray->mlx.x, ray->mlx.y);
	ray->mlx.data_addr = mlx_get_data_addr(ray->mlx.img_ptr,\
		&(ray->mlx.bpp), &(ray->mlx.size), &(ray->mlx.endian));
}

void	put_window(void *mlx_ptr, void *win_ptr, void *img)
{
	mlx_put_image_to_window(mlx_ptr, win_ptr, img, 0, 0);
}

int	loop(t_ray *ray)
{
	init_image(ray);
	if (ray->mv.w == 1)
		mv_frwrd(ray);
	if (ray->mv.a == 1)
		mv_left(ray);
	if (ray->mv.s == 1)
		mv_dwnwrd(ray);
	if (ray->mv.d == 1)
		mv_right(ray);
	// if (ray->mv.left == 1)
	// 	rot_left(ray);
	// if (ray->mv.right == 1)
	// 	rot_right(ray);
	raycast(ray);
	put_window(ray->mlx.mlx_ptr, ray->mlx.mlx_win, ray->mlx.img_ptr);
	return (0);
}

int	key_pressed(int key, t_ray *ray)
{
	if (key == ESC_KEY)
		win_close(ray);
	if (key == W_KEY)
		ray->mv.w = 1;
	if (key == A_KEY)
		ray->mv.a = 1;
	if (key == S_KEY)
		ray->mv.s = 1;
	if (key == D_KEY)
		ray->mv.d = 1;
	if (key == LEFT_KEY)
		ray->mv.left = 1;
	if (key == RIGHT_KEY)
		ray->mv.right = 1;
	loop(ray);
	return (0);
}

int	key_released(int key, t_ray *ray)
{
	if (key == ESC_KEY)
		win_close(ray);
	if (key == W_KEY)
		ray->mv.w = 0;
	if (key == A_KEY)
		ray->mv.a = 0;
	if (key == S_KEY)
		ray->mv.s = 0;
	if (key == D_KEY)
		ray->mv.d = 0;
	if (key == LEFT_KEY)
		ray->mv.left = 0;
	if (key == RIGHT_KEY)
		ray->mv.right = 0;
	loop(ray);
	return (0);
}

void    raycasting(t_parsing *parsing, t_elems *elems, t_ray *ray)
{
	ray->mlx.x = elems->R_x_value;
	ray->mlx.y = elems->R_y_value;
	ray->posx = (double)parsing->player_x + 0.5;
	ray->posy = (double)parsing->player_y + 0.5;
	ray->dda.mapx = (int)ray->posx;
	ray->dda.mapy = (int)ray->posy;
	ray->map[parsing->player_x][parsing->player_y] = '0';
	set_dir_plan(parsing->player_dir, ray);
	ray->resx = (double)elems->R_x_value;
	ray->resy =  (double)elems->R_y_value;
	mlx_hook(ray->mlx.mlx_win, KEYPRESS, 1L << 0, &key_pressed, ray);
	mlx_hook(ray->mlx.mlx_win, KEYRELEASE, 1L << 1, &key_released, ray);
	mlx_loop_hook(ray->mlx.mlx_ptr, &loop, ray);
	mlx_loop(ray->mlx.mlx_ptr);
}