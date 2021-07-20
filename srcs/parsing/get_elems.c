/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elems.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:57:20 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/05 17:55:50 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	final_check(char **final, int i)
{
	int	j;

	if (i != 3)
		return (1);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (final[i][j])
		{
			if (!(final[i][j] >= '0' && final[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	elem_present(t_elems *elems)
{
	if (elems->R_is_present == TRUE && elems->NO_is_present == TRUE
		&& elems->SO_is_present == TRUE && elems->WE_is_present == TRUE
		&& elems->EA_is_present == TRUE && elems->S_is_present == TRUE
		&& elems->F_is_present == TRUE && elems->C_is_present == TRUE)
		return (1);
	return (0);
}

void	stock_elem(char *newline, t_ray *ray, int elem_flag, t_elems *elems)
{
	if (elem_flag == 'R' || elem_flag == 'F' || elem_flag == 'C')
	{
		stock_values(newline, elem_flag, elems, ray);
		return ;
	}
	if (elem_flag == 'N' + 'O' || elem_flag == 'S' + 'O'
		|| elem_flag == 'W' + 'E' || elem_flag == 'E' + 'A'
		|| elem_flag == 'S')
	{
		get_path(newline, elem_flag, elems);
		free(newline);
		return ;
	}
}

void	elem_found(t_elems *elems, t_ray *ray, char *newline, int elem_flag)
{
	elem_flag = wich_elem(newline, elems);
	check_flag(elem_flag, elems);
	if (elems->double_elem)
		error_elems(newline, elems, 1);
	stock_elem(newline, ray, elem_flag, elems);
}

void	get_elems(int fd, t_elems *elems, t_ray *ray)
{
	char	*line;
	char	*newline;
	int		elem_flag;

	line = NULL;
	elem_flag = 0;
	while (get_next_line(fd, &line) == 1)
	{
		elems->error_fd = fd;
		if (elem_present(elems) == 1)
		{
			elems->last_elem_line = ft_strdup(line);
			free(line);
			return ;
		}
		newline = del_spaces(line);
		if (newline == NULL)
			error_elems(line, elems, 0);
		free(line);
		if (ft_strlen(newline) > 0)
			elem_found(elems, ray, newline, elem_flag);
		else
			free(newline);
	}
}
