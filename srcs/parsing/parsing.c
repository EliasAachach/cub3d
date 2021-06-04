#include "gnl/get_next_line.h"
#include "cub3d.h"

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

void	get_map(int fd, t_parsing *parsing)
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
			parsing->map[x] = ft_strdup(line);
			x++;
		}
		free(line);
	}
	if (x == parsing->nbr_lines - 1)
		parsing->map[x] = ft_strdup(line);
	free(line);
}

void	parser2(int fd, t_parsing *parsing, t_elems *elems)
{
	find_map(fd, parsing);
	parsing->nbr_lines_map = parsing->nbr_lines;
	elems->error_fd = fd;
	close(fd);
	if (parsing->map_error == TRUE)
		parse_error(parsing, elems, 0);
	fd = open(parsing->filename, O_RDONLY);
	get_map(fd, parsing);
	valid_map(parsing);
	if (parsing->map_is_open == TRUE || parsing->player_in_map == FALSE)
	{
		if (parsing->map_is_open == TRUE)
			parse_error(parsing, elems, 1);
		parse_error(parsing, elems, 0);
	}
	free(parsing->first_line);
	close(fd);
}

void	parser(t_parsing *parsing, t_elems *elems, char **arg, int nbr_arg)
{
	int		fd;
	char	*line;

	line = NULL;
	arg_check(arg, nbr_arg);
	parsing->filename = arg[1];
	fd = open(parsing->filename, O_RDONLY);
	get_elems(fd, elems);
	elems->error_fd = 0;
	last_line_check(elems->last_elem_line, parsing);
	if (check_all_elems(elems) == 1)
	{
		elems->error_fd = fd;
		error_elems(line, elems, 0);
	}
	if (rgb_check(elems) == 1)
	{
		elems->error_fd = fd;
		error_elems(line, elems, 5);
	}
	parser2(fd, parsing, elems);
}