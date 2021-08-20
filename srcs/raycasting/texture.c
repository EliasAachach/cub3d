/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:25:46 by user42            #+#    #+#             */
/*   Updated: 2021/08/20 15:35:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture(t_ray *ray, t_elems *elems)
{
	ray->img.addr[0] = mlx_xpm_file_to_image(ray->mlx.mlx_ptr, \
		elems->path_to_SO, &(ray->img.width), &(ray->img.height));
	if (ray->img.addr[0] == NULL)
		error_mlx(ray, 1);
	ray->img.addr[1] = mlx_xpm_file_to_image(ray->mlx.mlx_ptr, \
		elems->path_to_EA, &(ray->img.width), &(ray->img.height));
	if (ray->img.addr[1] == NULL)
		error_mlx(ray, 1);
	ray->img.addr[2] = mlx_xpm_file_to_image(ray->mlx.mlx_ptr, \
		elems->path_to_NO, &(ray->img.width), &(ray->img.height));
	if (ray->img.addr[2] == NULL)
		error_mlx(ray, 1);
	ray->img.addr[3] = mlx_xpm_file_to_image(ray->mlx.mlx_ptr, \
		elems->path_to_WE, &(ray->img.width), &(ray->img.height));
	if (ray->img.addr[3] == NULL)
		error_mlx(ray, 1);
}

void	init_texture(t_ray *ray, t_elems *elems)
{
	int	i;

	ray->img.addr = (void **)malloc(sizeof(void *) * 5);
	if (!ray->img.addr)
		error_mlx(ray, 1);
	ray->img.addr[4] = NULL;
	set_texture(ray, elems);
	ray->img.image = (char **)malloc(sizeof(char *) * 5);
	if (!ray->img.image)
		error_mlx(ray, 1);
	ray->img.image[4] = NULL;
	i = 0;
	while (i < 4)
	{
		ray->img.image[i] = mlx_get_data_addr(ray->img.addr[i], \
			&(ray->img.bpp), &(ray->img.s_line), &(ray->img.endian));
		i++;
	}
}
