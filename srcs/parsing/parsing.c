#include "../gnl/get_next_line.h"
#include "../../includes/cub3d.h"

char	**alloc_map(int nbr_lines, int longest_line)
{
	int		i;
	char	**map;

	i = 0;
	*map = ((char *)malloc(sizeof(char *) * (nbr_lines + 1)));
    if (!map)
        return (NULL);
	while (i <= nbr_lines)
	{
		map[i] = ((char *)malloc(sizeof(char) * (longest_line + 1)));
		if (!map[i])
			return (NULL);
		i++;
	}
	return (map);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	if (!(s2 = ((char *)malloc(sizeof(char) * (ft_strlen(s1) + 1)))))
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	find_map(int fd, t_parsing *parsing)
{
	int		first_line_passed;
	char	*line;

	line = NULL;
	first_line_passed = 0;
    while (get_next_line(fd, &line) == 1)
    {
		if (first_line_passed == 0 && line[0] != '\n')
		{
			parsing->first_line = ft_strdup(line);
			first_line_passed = 1;
		}
		if (line[0] == '\n'	&& first_line_passed == 1)
		{
			parsing->valid_map = NULL;
			free(parsing->first_line);
			free(line);
			return ;
		}
		if (!(line[0] == '\n'))
		{
			if (parsing->longest_line < ft_strlen(line))
				parsing->longest_line = ft_strlen(line);
			parsing->nbr_lines++;
		}
        free(line);
	}
	parsing->map = alloc_map(parsing->nbr_lines, parsing->longest_line);
    if (!parsing->map)
	{
		parsing->map_error = TRUE;
		return ;
	}
}

int	player_in_map(char c)
{
	if ( c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
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
	while (get_next_line(fd, &line) == 1 && first_line_passed == FALSE)
	{
		if (ft_strcmp(line, parsing->first_line) == 0)
		{
			parsing->map[x] = ft_strdup(line);
			x++;
			while (get_next_line(fd, &line) == 1 && x <= parsing->nbr_lines)
			{
				parsing->map[x] = ft_strdup(line);
				x++;
			}
		}
		first_line_passed = TRUE;
	}
}

void	flood_fill(t_parsing *parsing, int x, int y)
{
	//MAP OUVERTE
	if (x == 0 && parsing->map[x][y] != '1')
		parsing->map_is_open = 1;
	if (y == 0 && parsing->map[x][y] != '1')
		parsing->map_is_open = 1;
	if (x == parsing->nbr_lines && parsing->map[x][y] != '1')
		parsing->map_is_open = 1;
	if (y == parsing->longest_line && parsing->map[x][y] != '1')
		parsing->map_is_open = 1;
	//MAP OUVERTEfin
	if (x > parsing->highest_x)
		parsing->highest_x = x;
	if (x < parsing->lowest_x)
		parsing->lowest_x = x;
	if (y > parsing->highest_y)
		parsing->highest_y = y;
	if (y < parsing->lowest_y)
		parsing->lowest_x = x;
	if (parsing->map[x][y] == '1')
		parsing->map[x][y] = -2;
	if (parsing->map[x][y] == '0' || parsing->map[x][y] == '2')
	{
		if (parsing->map[x][y] == '2')
			parsing->map[x][y] = -3;
		else
			parsing->map[x][y] = -1;
		flood_fill(parsing, x, y + 1);
		flood_fill(parsing, x, y - 1);
		flood_fill(parsing, x + 1, y);
		flood_fill(parsing, x - 1, y);
	}
}

void	valid_map(t_parsing *parsing)
{
	int	x;
	int	y;

	x = 0;
	while (parsing->map[x])
	{
		y = 0;
		while (parsing->map[x][y])
		{
			if (player_in_map(parsing->map[x][y]) == 1)
			{
				parsing->player_x = x;
				parsing->player_y = y;
				parsing->lowest_x = parsing->player_x;
				parsing->lowest_y = parsing->player_y;
				flood_fill(parsing, x, y);
				parsing->nbr_lines = parsing->highest_x - parsing->lowest_x;
				parsing->longest_line = parsing->highest_y - parsing->lowest_y;
				return ;
			}
			y++;
		}
		x++;
	}
}

void	get_valid_map(t_parsing *parsing)
{
	int i;
	int j;
	int x;
	int y;

	x = 0;
	i = parsing->lowest_x;
	while (i <= parsing->highest_x)
	{
		j = parsing->lowest_y;
		y = 0;
		while (parsing->map[i] || j <= parsing->highest_y)
		{
			if (parsing->map[i][j] == -1)
				parsing->valid_map[x][y] = 0;
			if (parsing->map[i][j] == -2)
				parsing->valid_map[x][y] = 1;
			if (parsing->map[i][j] == -3)
				parsing->valid_map[x][y] = 2;
		}
		i++;
		x++;
	}
}

int		check_next_char(char *charset, int i)
{
	if (charset[i] == 'S' || charset[i] == 'N')
	{
		if (charset[i + 1] == 'O')
			return ('S' + 'O');
		else if (charset[i] == 'S')
			return ('S');
	}
	else if (charset[i] == 'W')
	{
		if (charset[i + 1] == 'E')
			return ('W' + 'E');
		else
			return (0);
	}
	else if (charset[i] == 'E')
	{
		if (charset[i + 1] == 'A')
			return ('E' + 'A');
		else
			return (0);
	}
}

char	wich_elem(char *line, t_elems *elems)
{
	char	*charset;
	int		i;

	i = 0;
	charset = "RNSWEFC";
	while (charset[i])
	{
		if (line[0] == charset[i])
		{
			return (check_next_char(charset, i));
		}
		i++;
	}
	error_elems(line, elems, 0);
	return (NULL);
}

char 	*del_spaces(char *line)
{
	int i;
	int len;
	char *newline;

	i = 0;
	len = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	newline = ft_strdup(line + i);
	if (!newline)
		return (NULL);
	return (newline);
}

void	error_elems(char *newline, t_elems *elems, int error_flag)
{
	if (error_flag == 0)
		printf("Error : an element is missing.");
	if (error_flag == 1)
		printf("Error : an element is present mutiple times.");
	if (error_flag == 3)
		printf("Unexpected error, check your map.");
	if (error_flag == 4)
		printf("Error : map is invalid.");
	ft_free(newline, elems);
	exit(0);
}

void	get_R_values(char *newline, t_elems *elems)
{
	int i;

	i = 1;
	while (!(newline[i] >= '0' && newline[i] <= '9'))
	{
		if (!(newline[i] == ' ' || newline[i] == '	'))
			error_elems(newline, elems, 0);
		i++;
	}
	elems->R_x_value = ft_atoi(newline + i);
	while (newline[i] >= '0' && newline[i] <= '9')
		i++;
	while (!(newline[i] >= '0' && newline[i] <= '9'))
	{
		if (!(newline[i] == ' ' || newline[i] == '	'))
			error_elems(newline, elems, 0);
		i++;
	}
	elems->R_y_value = ft_atoi(newline + i);
}

int		ft_strdup_path2(char *tmp, int elem_flag, t_elems *elems)
{
	if (elem_flag == 'E' + 'A')
	{
		elems->path_to_EA = ft_strdup(tmp);
		if (elems->path_to_EA == NULL)
			return (1);
		retrun (0);
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

void	get_path(char *newline, int elem_flag, t_elems *elems)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	if (elem_flag == 'S')
		i = 1;
	else
		i = 2;
	while ((newline[i] == ' ' || newline[i] == '	') && newline[i])
		i++;
	while (!(newline[i] == ' ' || newline[i] == '	') && newline[i])
	{
		tmp[j] = newline[i];
		i++;
		j++;
	}
	if (ft_strdup_path(tmp, elem_flag, elems) == 1)
		error_elems(newline, elems, 0);
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

void	color_code(char *newline, int elem, int rgb, t_elems *elems)
{
	if (elem == 'F')
	{
		if (rgb == 'r')
			elems->r_F = ft_atoi(newline);
		if (rgb == 'g')
			elems->g_F = ft_atoi(newline);
		if (rgb == 'b')
			elems->b_F = ft_atoi(newline);
	}
	if (elem == 'C')
	{
		if (rgb == 'r')
			elems->r_C = ft_atoi(newline);
		if (rgb == 'g')
			elems->g_C = ft_atoi(newline);
		if (rgb == 'b')
			elems->b_C = ft_atoi(newline);
	}
}

void	get_colors(char	*newline, int elem_flag, t_elems *elems)
{
	int	i;

	i = 1;
	while (!(newline[i] >= '0' && newline[i] <= '9'))
	{
		if (!(newline[i] == ' ' || newline[i] == '	'))
			error_elems(newline, elems, 0);
		i++;
	}
	check_colors(newline, elem_flag, elems, i);
	if (!(newline[i + 3] == ','))
		error_elems(newline, elems, 0);
	color_code(newline + i, elem_flag, 'r', elems);
	i += 3;
	if (!(newline[i + 2] == ','))
		error_elems(newline, elems, 0);
	color_code(newline + i, elem_flag, 'g', elems);
	i += 3;
	if (!(newline[i + 2] == ' ') || !(newline[i] == '	')
		|| !(newline[i] == '\0'))
		error_elems(newline, elems, 0);
	color_code(newline + i, elem_flag, 'b', elems);
}

void	stock_values(char *newline, int elem_flag, t_elems *elems)
{
	if (elem_flag == 'R')
		get_R_values(elems, newline);
	if (elem_flag == 'F' || elem_flag == 'C')
		get_colors(newline, elem_flag, elems);
}

void	stock_elem(char *newline, int elem_flag, t_elems *elems)
{
	if (elem_flag == 'R' || elem_flag == 'F' || elem_flag == 'C')
	{
		stock_values(newline, elem_flag, elems);
		return ;
	}
	if (elem_flag == 'NO' || elem_flag == 'SO'
		|| elem_flag == 'WE' || elem_flag == 'EA'
		|| elem_flag == 'S')
	{
			get_path(newline, elem_flag, elems);
			return ;
	}
}

void	check_flag4(int elem_flag, t_elems *elems)
{
	if (elem_flag == 'F')
	{
		if (elems->F_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->F_is_present = TRUE;
		return ;
	}
	if (elem_flag == 'C')
	{
		if (elems->C_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->C_is_present = TRUE;
		return ;
	}
}

void	check_flag3(int elem_flag, t_elems *elems)
{
	if (elem_flag == 'R')
	{
		if (elems->R_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->R_is_present = TRUE;
		return ;
	}
	if (elem_flag == 'S')
	{
		if (elems->S_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->S_is_present = TRUE;
		return ;
	}
	check_flag4(elem_flag, elems);
}

void	check_flag2(int elem_flag, t_elems *elems)
{
	if (elem_flag == 'W' + 'E')
	{
		if (elems->WE_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->WE_is_present = TRUE;
		return ;
	}
	if (elem_flag == 'E' + 'A')
	{
		if (elems->EA_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->EA_is_present = TRUE;
		return ;
	}
	check_flag3(elem_flag, elems);
}

void	check_flag(int elem_flag, t_elems *elems)
{
	if (elem_flag == 'N' + 'O')
	{
		if (elems->NO_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->NO_is_present = TRUE;
		return ;
	}
	if (elem_flag == 'S' + 'O')
	{
		if (elems->SO_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->SO_is_present = TRUE;
		return ;
	}
	check_flag2(elem_flag, elems);
}

ft_free(char *newline, t_elems *elems)
{
	if (newline)
		free(newline);
	if (elems->path_to_S)
		free(elems->path_to_S);
	if (elems->path_to_NO)
		free(elems->path_to_NO);
	if (elems->path_to_SO)
		free(elems->path_to_SO);
	if (elems->path_to_EA)
		free(elems->path_to_EA);
	if (elems->path_to_WE)
		free(elems->path_to_WE);
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

int		elem_present(t_elems *elems)
{
	if (elems->R_is_present == TRUE || elems->NO_is_present == TRUE
		|| elems->SO_is_present == TRUE || elems->WE_is_present == TRUE
		|| elems->EA_is_present == TRUE || elems->S_is_present == TRUE
		|| elems->F_is_present == TRUE || elems->C_is_present == TRUE)
			return (1);
		return (0);
}

void	get_elems(int fd, t_elems *elems)
{
	char	*line;
	char	*newline;
	int		elem_flag;

	line = NULL;
	elem_flag = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (elem_present(elems) == 1)
			return ;
		newline = del_spaces(line);
		free(line);
		elem_flag = wich_elem(newline, elems);
		check_flag(elem_flag, &elems);
		if (elems->double_elem)
			error_elems(newline, elems, 1);
		stock_elem(newline, elem_flag, elems);
	}
}

void	pass_empty_lines(fd)
{
	char	*line;

	line = NULL;
	while ((get_next_line(fd, &line) == 1) && line == "\n")
	{
		if (!(line == "\n"))
			return (line);
	}
	return (line);
}

void	parsing(t_parsing *parsing)
{
	int		fd;
	char	*line;
	t_elems	elems;

	fd = open(parsing->filename, O_RDONLY);
	get_elems(fd, &elems);
		if (check_all_elems(&elems) == 1)
			error_elems(line, &elems, 0);
	line = NULL;
	find_map(fd, parsing);
	if (parsing->valid_map == NULL || parsing->map_error = TRUE)
		error_elems(line, &elems, 4);
	fd = open(parsing->filename, O_RDONLY);
	get_map(fd, parsing);
	valid_map(parsing);
	parsing->valid_map = alloc_map(parsing->nbr_lines, parsing->longest_line);
	get_valid_map(parsing);
}