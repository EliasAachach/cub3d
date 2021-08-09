/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:29:53 by user42            #+#    #+#             */
/*   Updated: 2021/08/09 00:09:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_mlx2(t_ray *ray, int error_malloc)
{
	if (error_malloc == 1)
	{
		mlx_clear_window(ray->mlx.mlx_ptr, ray->mlx.mlx_win);
		mlx_destroy_window(ray->mlx.mlx_ptr, ray->mlx.mlx_win);
	}
	if (ray->err.NO)
		free(ray->err.NO);
	if (ray->err.SO)
		free(ray->err.SO);
	if (ray->err.EA)
		free(ray->err.EA);
	if (ray->err.WE)
		free(ray->err.WE);
	free_texture(ray);
}

void	error_mlx(t_ray *ray, int error_malloc)
{
	int	i;

	i = 0;
	if (error_malloc == 1)
		printf("Error\nMalloc error, something went wrong.\n");
	error_mlx2(ray, error_malloc);
	if (ray->mlx.mlx_ptr)
	{
		mlx_destroy_display(ray->mlx.mlx_ptr);
		free(ray->mlx.mlx_ptr);
	}
	if (ray->map)
	{
		while (ray->map[i])
		{
			free(ray->map[i]);
			i++;
		}
		free(ray->map);
	}
	exit(0);
}

void	error_elems(char *newline, t_elems *elems, t_ray *ray)
{
	char	*line;

	line = NULL;
	while (get_next_line(elems->error_fd, &line) == 1)
		free(line);
	free(line);
	if (elems->err_flag != 6)
		mlx_destroy_display(ray->mlx.mlx_ptr);
	if (ray->mlx.mlx_ptr)
		free(ray->mlx.mlx_ptr);
	if (elems->err_flag == 0)
		printf("Error\nAn element is missing or wrong.\n");
	if (elems->err_flag == 1)
		printf("Error\nAn element is present mutiple times.\n");
	if (elems->err_flag == 3)
		printf("Error\nUnexpected error, check your map.\n");
	if (elems->err_flag == 4)
		printf("Error\nMap is invalid.\n");
	if (elems->err_flag == 5)
		printf("Error\nAn element is incorrect.\n");
	ft_free(newline, elems);
	exit(0);
}
