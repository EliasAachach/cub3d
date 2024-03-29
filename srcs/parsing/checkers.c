/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 23:26:06 by elaachac          #+#    #+#             */
/*   Updated: 2021/08/18 17:04:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_colors(char *newline, int elem_flag, t_elems *elems, int i)
{
	int	all;
	int	coma;
	int	color;

	all = 0;
	coma = 0;
	color = 0;
	while ((newline[i] >= '0' && newline[i] <= '9') || newline[i] == ',')
	{
		if (coma > 2 || color > 3 || all > 11)
		{
			error_elems(newline, elems, 0);
		}
		if (newline[i] == ',')
		{
			coma++;
			color = 0;
		}
		i++;
		all++;
		color++;
	}
}

int	check_all_elems(t_elems *elems)
{
	if (elems->R_is_present == FALSE || elems->NO_is_present == FALSE
		|| elems->EA_is_present == FALSE || elems->SO_is_present == FALSE
		|| elems->WE_is_present == FALSE || elems->C_is_present == FALSE
		|| elems->F_is_present == FALSE)
		return (1);
	return (0);
}

void	arg_check(char **arg, int nbr_arg, t_ray *ray)
{
	int	fd;

	if (nbr_arg != 2)
	{
		if (ray->mlx.mlx_ptr)
		{
			mlx_destroy_display(ray->mlx.mlx_ptr);
			free(ray->mlx.mlx_ptr);
		}
		printf("Error\nWrong number of arguments.\n");
		exit(0);
	}
	fd = open(arg[1], O_RDONLY);
	if (ft_strcmp(arg[1] + ft_strlen(arg[1]) - 4, ".cub") != 0 || fd < 0)
	{
		close(fd);
		printf("Error\nFile is invalid.\n");
		if (ray->mlx.mlx_ptr)
		{
			mlx_destroy_display(ray->mlx.mlx_ptr);
			free(ray->mlx.mlx_ptr);
		}
		exit(0);
	}
	close(fd);
}
