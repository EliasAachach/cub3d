#include "gnl/get_next_line.h"
#include "cub3d.h"

char	**alloc_map(int nbr_lines, int longest_line)
{
	int		i;
	char	**map;

	i = 0;
	map = ((char **)malloc(sizeof(char *) * (nbr_lines + 1)));
	map[nbr_lines] = NULL;
	if (!map)
		return (NULL);
	return (map);
}

int		is_first_line(char *line)
{
	int i;

	i = 0;
	while (ft_strlen(line) > 0 && line[i])
	{
		if (line[i] == ' ' || line[i] == '	')
		{
			i++;
		}
		else
			return (1);
	}
	return (0);
}

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

int		check_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
				return (1);
		i++;
	}
	return (0);
}

void	error_last_line(t_parsing *parsing, char *line, char *newline)
{
		parsing->map_error = TRUE;
		free(parsing->first_line);
		free(line);
		free(newline);
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

void	first_line_false(t_parsing *parsing, char *line)
{
	if (is_first_line(line) == 1)
	{
		parsing->first_line = ft_strdup(line);
		parsing->first_line_passed = TRUE;
	}
}

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

void	find_map(int fd, t_parsing *parsing)
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
	free(line);
	parsing->map = alloc_map(parsing->nbr_lines, parsing->longest_line);
    if (!parsing->map)
	{
		parsing->map_error = TRUE;
		return ;
	}
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

int		check_next_char(char *line)
{
	if (line[0] == 'S' || line[0] == 'N')
	{
		if (line[1] == 'O')
		{
			if (line[0] == 'S')
				return ('S' + 'O');
			else
				return ('N' + 'O');
		}
		else if (line[0] == 'S')
			return ('S');
	}
	else if (line[0] == 'W')
	{
		if (line[1] == 'E')
			return ('W' + 'E');
		else
			return (0);
	}
	else if (line[0] == 'E')
	{
		if (line[1] == 'A')
			return ('E' + 'A');
		else
			return (0);
	}
	return (0);
}

int		wich_elem(char *line, t_elems *elems)
{
	char	*charset;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	charset = "RNSWEFC";
	while (charset[i])
	{
		if (line[0] == charset[i])
		{
			ret = charset[i];
			if (!(charset[i] == 'R' || charset[i] == 'F' || charset[i] == 'C'))
			{
				ret = check_next_char(line);
				if (ret == 0)
					error_elems(line, elems, 0);
			}
			return (ret);
		}
		i++;
	}
	error_elems(line, elems, 0);
	return (0);
}

int		res_check(char *str, t_elems *elems)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	elems->mlx_ptr = mlx_init();
	mlx_get_screen_size(elems->mlx_ptr, (&x), (&y));
	while(str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	if (elems->R_x_value <= 0 || elems->R_y_value <= 0)
		return (1);
	if (elems->R_x_value > x)
		elems->R_x_value = x;
	if (elems->R_y_value > y)
		elems->R_y_value = y;
	return (0);
}

int		ft_strdup_path2(char *tmp, int elem_flag, t_elems *elems)
{
	if (elem_flag == 'E' + 'A')
	{
		elems->path_to_EA = ft_strdup(tmp);
		if (elems->path_to_EA == NULL)
			return (1);
		return (0);
	}
	if (elem_flag == 'W' + 'E')
	{
		elems->path_to_WE = ft_strdup(tmp);
		if (elems->path_to_WE == NULL)
			return (1);
		return (0);
	}
	return (1);
}

int		ft_strdup_path(char *tmp, int elem_flag, t_elems *elems)
{
	if (elem_flag == 'S')
	{
		elems->path_to_S = ft_strdup(tmp);
		if (elems->path_to_S == NULL)
			return (1);
		return (0);
	}
	if (elem_flag == 'N' + 'O')
	{
		elems->path_to_NO = ft_strdup(tmp);
		if (elems->path_to_NO == NULL)
			return (1);
		return (0);
	}
		if (elem_flag == 'S' + 'O')
		{
			elems->path_to_SO = ft_strdup(tmp);
			if (elems->path_to_SO == NULL)
				return (1);
			return (0);
		}
	return (ft_strdup_path2(tmp, elem_flag, elems));
}

int		existing_path(char *tmp)
{
	int	fd;

	fd = open(tmp, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
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

int		final_check(char **final, int i)
{
	int j;

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