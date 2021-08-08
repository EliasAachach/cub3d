/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:38:42 by elaachac          #+#    #+#             */
/*   Updated: 2021/08/08 23:24:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	win_close(t_ray *ray)
{
	if (ray->mlx.img_ptr)
		mlx_destroy_image(ray->mlx.mlx_ptr, ray->mlx.img_ptr);
	if (ray->mlx.mlx_ptr && ray->mlx.mlx_win)
	{
		mlx_clear_window(ray->mlx.mlx_ptr, ray->mlx.mlx_win);
		mlx_destroy_window(ray->mlx.mlx_ptr, ray->mlx.mlx_win);
	}
	printf("Exiting Cub3d\n");
	error_mlx(ray, 0);
	exit(0);
	return (0);
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
	if (ray->mv.left == 1)
		rot_left(ray);
	if (ray->mv.right == 1)
		rot_right(ray);
	raycast(ray);
	put_window(ray->mlx.mlx_ptr, ray->mlx.mlx_win, ray->mlx.img_ptr);
	return (0);
}

void	raycasting(t_parsing *parsing, t_elems *elems, t_ray *ray)
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
	ray->resy = (double)elems->R_y_value;
	err_ptr(ray, elems);
	init_texture(ray, elems);
	mlx_hook(ray->mlx.mlx_win, KEYPRESS, 1L << 0, &key_pressed, ray);
	mlx_hook(ray->mlx.mlx_win, KEYRELEASE, 1L << 1, &key_released, ray);
	mlx_loop_hook(ray->mlx.mlx_ptr, &loop, ray);
	mlx_loop(ray->mlx.mlx_ptr);
}
