/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 13:53:06 by elaachac          #+#    #+#             */
/*   Updated: 2021/08/17 14:01:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "../../includes/cub3d.h"

void	last_line_check(char *line, t_parsing *parsing)
{
	if (is_first_line(line) == 1)
	{
		parsing->first_line = ft_strdup(line);
		parsing->first_line_passed = 1;
		parsing->longest_line = ft_strlen(line);
		parsing->nbr_lines++;
	}
	free(line);
}

void	get_map(int fd, t_parsing *parsing, t_ray *ray)
{
	int		x;
	int		first_line_passed;
	char	*line;

	first_line_passed = FALSE;
	line = NULL;
	x = 0;
	while (get_next_line(fd, &line))
	{
		if ((ft_strcmp(line, parsing->first_line) == 0
				|| first_line_passed == TRUE) && x <= parsing->nbr_lines)
		{
			first_line_passed = TRUE;
			ray->map[x] = ft_strdup(line);
			x++;
		}
		free(line);
	}
	if (x == parsing->nbr_lines - 1)
		ray->map[x] = ft_strdup(line);
	free(line);
}

void	parser2(int fd, t_parsing *parsing, t_elems *elems, t_ray *ray)
{
	find_map(fd, parsing, ray);
	parsing->nbr_lines_map = parsing->nbr_lines;
	elems->error_fd = fd;
	if (parsing->map_error == TRUE)
		parse_error(parsing, elems, 8, ray);
	fd = open(parsing->filename, O_RDONLY);
	get_map(fd, parsing, ray);
	valid_map(parsing, ray);
	if (parsing->map_is_open == TRUE || parsing->player_in_map == FALSE)
	{
		if (parsing->map_is_open == TRUE)
			parse_error(parsing, elems, 1, ray);
		parse_error(parsing, elems, 0, ray);
	}
	free(parsing->first_line);
	close(fd);
}

void	parser(t_parsing *parsing, t_elems *elems, t_ray *ray, char **arg)
{
	int		fd;
	char	*line;

	line = NULL;
	arg_check(arg, parsing->nbr_arg, ray);
	parsing->filename = arg[1];
	fd = open(parsing->filename, O_RDONLY);
	get_elems(fd, elems, ray);
	elems->error_fd = 0;
	last_line_check(elems->last_elem_line, parsing);
	if (check_all_elems(elems) == 1)
	{
		elems->err_flag = 0;
		elems->error_fd = fd;
		error_elems(line, elems, ray);
	}
	if (rgb_check(elems) == 1)
	{
		elems->err_flag = 5;
		elems->error_fd = fd;
		error_elems(line, elems, ray);
	}
	parser2(fd, parsing, elems, ray);
}
