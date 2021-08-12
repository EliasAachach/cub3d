/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:53:49 by elaachac          #+#    #+#             */
/*   Updated: 2021/08/12 14:52:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	end_of_loop(t_parsing *parsing, char *line, char *newline)
{
	if (!(line[0] == '\0'))
	{
		if (parsing->longest_line < ft_strlen(line))
			parsing->longest_line = ft_strlen(line);
		parsing->nbr_lines++;
	}
	free(line);
	free(newline);
}

void	error_last_line(t_parsing *parsing, char *line, char *newline)
{
	parsing->map_error = TRUE;
	free(parsing->first_line);
	free(line);
	free(newline);
}

void	first_line_false(t_parsing *parsing, char *line)
{
	if (is_first_line(line) == 1)
	{
		parsing->first_line = ft_strdup(line);
		parsing->first_line_passed = TRUE;
	}
}

void	last_line(char *line, t_parsing *parsing)
{
	char	*newline;

	if (parsing->first_line_passed == 0)
	{
		if (is_first_line(line) == 1)
		{
			parsing->first_line = ft_strdup(line);
			parsing->first_line_passed = 1;
		}
	}
	newline = del_spaces(line);
	if (((newline[0] == '\0' || check_line(newline) == 1)
			&& parsing->first_line_passed == 1) || newline == NULL)
	{
		error_last_line(parsing, line, newline);
		return ;
	}
	if (!(line[0] == '\0'))
	{
		if (parsing->longest_line < ft_strlen(line))
			parsing->longest_line = ft_strlen(line);
		parsing->nbr_lines++;
	}
	free(newline);
}

void	find_map(int fd, t_parsing *parsing, t_ray *ray)
{
	char	*line;
	char	*newline;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (parsing->first_line_passed == FALSE)
			first_line_false(parsing, line);
		newline = del_spaces(line);
		if (((newline[0] == '\0' || check_line(newline) == 1)
				&& parsing->first_line_passed == 1) || newline == NULL)
		{
			error_last_line(parsing, line, newline);
			return ;
		}
		end_of_loop(parsing, line, newline);
	}
	last_line(line, parsing);
	if (parsing->map_error == TRUE)
		return ;
	free(line);
	ray->map = alloc_map(parsing->nbr_lines, parsing->longest_line);
	if (!ray->map)
	{
		parsing->map_error = TRUE;
		return ;
	}
}
