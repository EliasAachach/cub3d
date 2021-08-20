/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elems_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:41:21 by user42            #+#    #+#             */
/*   Updated: 2021/08/19 14:05:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_get_elems(int *elem_flag, t_elems *elems)
{
	elem_flag = 0;
	elems->err_flag = 0;
}

void	get_elems_2(char *newline, char *line, t_elems *elems, t_ray *ray)
{
	int	elem_flag;

	elem_flag = 0;
	if (elem_present(elems) == 1)
	{
		elems->last_elem_line = ft_strdup(line);
		free(line);
		return ;
	}
	newline = del_spaces(line);
	if (newline == NULL)
		error_elems(line, elems, ray);
	free(line);
	if (ft_strlen(newline) > 0)
		elem_found(elems, ray, newline, elems->flag_elem);
	else
		free(newline);
}
