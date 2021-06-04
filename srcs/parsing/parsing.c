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

char 	*del_spaces(char *line)
{
	int		i;
	char	*newline;

	i = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	newline = ft_strdup(line + i);
	if (!newline)
		return (NULL);
	return (newline);
}

int		player_in_map(char c, t_parsing *parsing)
{
	if ( c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		parsing->player_in_map = TRUE;
		return (1);
	}
	else
		return (0);
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

void	get_valid_map(t_parsing *parsing, char **ff_map)
{
	int		i;

	i = 0;
	while (i < parsing->nbr_lines)
	{
		ff_map[i] = ft_strdup(parsing->map[i]);
		i++;
	}
}

void	valid_map(t_parsing *parsing)
{
	int		x;
	int		y;
	char	**ff_map;

	x = 0;
	ff_map = alloc_map(parsing->nbr_lines, parsing->longest_line);
	get_valid_map(parsing, ff_map);
	while (x < parsing->nbr_lines)
	{
		y = 0;
		while (ff_map[x][y])
		{
			if (player_in_map(ff_map[x][y], parsing) == 1)
			{
				parsing->player_x = x;
				parsing->player_y = y;
				ff_map[x][y] = '0';
				flood_fill(parsing, ff_map, x, y);
				ft_strfree(ff_map);
				return ;
			}
			y++;
		}
		x++;
	}
	ft_strfree(ff_map);
}

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
			error_elems(newline, elems, 0);
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

int		check_all_elems(t_elems *elems)
{
	if (elems->R_is_present == FALSE || elems->NO_is_present == FALSE ||
		elems->EA_is_present == FALSE || elems->SO_is_present == FALSE ||
		elems->WE_is_present == FALSE || elems->S_is_present == FALSE ||
		elems->C_is_present == FALSE || elems->F_is_present == FALSE)
			return (1);
	return (0);
}

void	arg_check(char **arg, int nbr_arg)
{
	int fd;

	if (nbr_arg != 2)
	{
		printf("Error\nWrong number of arguments.");
		exit(0);
	}
	fd = open(arg[1], O_RDONLY);
	if (fd < 0)

	if (ft_strcmp(arg[1] + ft_strlen(arg[1]) - 4, ".cub") == 1 || fd < 0)
	{
		close(fd);
		printf("Error\nFile is invalid");
		exit(0);
	}
	close(fd);
}

int		rgb_check(t_elems *elems)
{
	if (!(elems->r_F >= 0 && elems->r_F <= 255))
		return (1);
	if (!(elems->g_F >= 0 && elems->g_F <= 255))
		return (1);
	if (!(elems->b_F >= 0 && elems->b_F <= 255))
		return (1);
	if (!(elems->r_C >= 0 && elems->r_C <= 255))
		return (1);
	if (!(elems->g_C >= 0 && elems->g_C <= 255))
		return (1);
	if (!(elems->b_C >= 0 && elems->b_C <= 255))
		return (1);
	return (0);
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