/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elems_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:09:35 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/04 16:17:34 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	get_R_values(char *newline, t_elems *elems)
{
	int i;

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
	if (res_check(newline + i, elems) == 1)
		error_elems(newline, elems, 5);
	free(newline);
}

void	stock_values(char *newline, int elem_flag, t_elems *elems)
{
	if (elem_flag == 'R')
		get_R_values(newline, elems);
	if (elem_flag == 'F' || elem_flag == 'C')
		get_colors(newline, elem_flag, elems);
}