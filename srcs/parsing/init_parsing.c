/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:43:53 by user42            #+#    #+#             */
/*   Updated: 2021/08/08 19:46:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parsing2(t_parsing *parsing, t_elems *elems, int argc, t_ray *ray)
{
	elems->S_is_present = 0;
	elems->F_is_present = 0;
	elems->C_is_present = 0;
	elems->missing_elem = 0;
	elems->double_elem = 0;
	elems->R_x_value = 0;
	elems->R_y_value = 0;
	elems->r_F = 0;
	elems->g_F = 0;
	elems->b_F = 0;
	elems->r_C = 0;
	elems->g_C = 0;
	elems->b_C = 0;
	elems->error_fd = 0;
	elems->path_to_S = NULL;
	elems->path_to_NO = NULL;
	elems->path_to_SO = NULL;
	elems->path_to_EA = NULL;
	elems->path_to_WE = NULL;
	ray->mlx.mlx_ptr = mlx_init();
}

void	init_parsing(t_parsing *parsing, t_elems *elems, int argc, t_ray *ray)
{
	parsing->filename = NULL;
	parsing->first_line = NULL;
	ray->map = NULL;
	parsing->valid_map = NULL;
	parsing->longest_line = 0;
	parsing->nbr_lines = 0;
	parsing->player_x = 0;
	parsing->player_y = 0;
	parsing->player_exists = 0;
	parsing->highest_x = 0;
	parsing->lowest_x = 0;
	parsing->highest_y = 0;
	parsing->lowest_y = 0;
	parsing->map_is_open = 0;
	parsing->map_error = 0;
	parsing->player_in_map = 0;
	parsing->first_line_passed = 0;
	parsing->nbr_arg = argc;
	elems->R_is_present = 0;
	elems->NO_is_present = 0;
	elems->SO_is_present = 0;
	elems->WE_is_present = 0;
	elems->EA_is_present = 0;
	init_parsing2(parsing, elems, argc, ray);
}
