/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elems_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:09:35 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/06 20:27:40 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	color_code(char **final, int elem, t_elems *elems)
{
	if (elem == 'F')
	{
		elems->r_F = ft_atoi(final[0]);
		elems->g_F = ft_atoi(final[1]);
		elems->b_F = ft_atoi(final[2]);
	}
	if (elem == 'C')
	{
		elems->r_C = ft_atoi(final[0]);
		elems->g_C = ft_atoi(final[1]);
		elems->b_C = ft_atoi(final[2]);
	}
	free(final[0]);
	free(final[1]);
	free(final[2]);
	free(final);
}

void	get_colors2(char **final, int i, int elem_flag, t_elems *elems)
{
	if (ft_strlen(final[0]) > 3 || ft_strlen(final[1]) > 3
		|| ft_strlen(final[2]) > 3 || i != 3 || final_check(final, i) == 1)
	{
		while (i >= 0)
		{
			free(final[i]);
			i--;
		}
		free(final);
		error_elems(NULL, elems, 5);
	}
	color_code(final, elem_flag, elems);
}

void	get_colors(char *newline, int elem_flag, t_elems *elems)
{
	int		i;
	char	*line;
	char	**final;

	i = 0;
	line = ft_strtrim(newline + 1, " 	");
	if (!line)
		error_elems(newline, elems, 3);
	free(newline);
	final = ft_split(line, ',');
	free(line);
	if (!final)
		error_elems(line, elems, 3);
	while (final[i])
	{
		final[i] = ft_strtrim_inside(final[i]);
		i++;
	}
	get_colors2(final, i, elem_flag, elems);
}

void	get_R_values(char *newline, t_elems *elems, t_ray *ray)
{
	int	i;

	i = 1;
	while (!(newline[i] >= '0' && newline[i] <= '9'))
	{
		if (!(newline[i] == ' ' || newline[i] == '	'))
			error_elems(newline, elems, 5);
		i++;
	}
	elems->R_x_value = ft_atoi(newline + i);
	while (newline[i] >= '0' && newline[i] <= '9')
		i++;
	while (!(newline[i] >= '0' && newline[i] <= '9'))
	{
		if (!(newline[i] == ' ' || newline[i] == '	'))
			error_elems(newline, elems, 5);
		i++;
	}
	elems->R_y_value = ft_atoi(newline + i);
	if (res_check(newline + i, elems, ray) == 1)
		error_elems(newline, elems, 5);
	free(newline);
}

void	stock_values(char *newline, int elem_flag, t_elems *elems, t_ray *ray)
{
	if (elem_flag == 'R')
		get_R_values(newline, elems, ray);
	if (elem_flag == 'F' || elem_flag == 'C')
		get_colors(newline, elem_flag, elems);
}
