/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:27:26 by user42            #+#    #+#             */
/*   Updated: 2021/08/12 15:29:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_parsing(t_parsing *parsing, t_ray *ray)
{
	int	i;

	i = 0;
	if (parsing->first_line)
		free(parsing->first_line);
	if (ray->map)
	{
		while (ray->map[i])
		{
			free(ray->map[i]);
			i++;
		}
		free(ray->map);
	}
}

void	parse_error(t_parsing *parsing, t_elems *elems, int error_flag, \
	t_ray *ray)
{
	if (error_flag == 0)
		printf("Error\nMap is invalid.\n");
	if (error_flag == 1)
		printf("Error\nMap is open.\n");
	free_parsing(parsing, ray);
	elems->err_flag = 9;
	error_elems(NULL, elems, ray);
	exit(0);
}

void	ft_free(char *newline, t_elems *elems)
{
	if (newline)
		free(newline);
	if (elems->path_to_S)
		free(elems->path_to_S);
	if (elems->path_to_NO)
		free(elems->path_to_NO);
	if (elems->path_to_SO)
		free(elems->path_to_SO);
	if (elems->path_to_EA)
		free(elems->path_to_EA);
	if (elems->path_to_WE)
		free(elems->path_to_WE);
}

void	free_texture(t_ray *ray)
{
	int	i;

	i = 0;
	while (ray->img.addr[i])
	{
		if (ray->img.addr[i])
			mlx_destroy_image(ray->mlx.mlx_ptr, ray->img.addr[i]);
		i++;
	}
	if (ray->img.addr)
		free(ray->img.addr);
	if (ray->img.image)
		free(ray->img.image);
}

void	err_ptr(t_ray *ray, t_elems *elems)
{
	ray->err.NO = elems->path_to_NO;
	ray->err.SO = elems->path_to_SO;
	ray->err.WE = elems->path_to_WE;
	ray->err.EA = elems->path_to_EA;
}
