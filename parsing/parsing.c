#include "gnl/get_next_line.h"
#include "cub3d.h"

void	ft_putstr_fd(char *s)
{
	if (s)
	{
		write(1, s, ft_strlen(s));
	}
}

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

/*size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}*/

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int		ft_atoi(const char *str)
{
	int i;
	int neg;
	int nb;

	i = 0;
	nb = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * neg);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}

char	*ft_strndup(char *s1, int len, int i)
{
	int		j;
	char	*s2;

	j = 0;
	s2 = ((char *)malloc(sizeof(char) * (len + 1)));
	if (!s2)
		return (NULL);
	while (s1[i] && j <= len)
	{
		s2[j] = s1[i];
		i++;
		j++;
	}
	s2[j] = '\0';
	return (s2);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = ((char *)malloc(sizeof(char) * (ft_strlen(s1) + 1)));
	if (!s2)
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
		if (line[0] == '\n' && first_line_passed == 1)
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
	if (x == 0 && parsing->map[x][y] != '1')
		parsing->map_is_open = 1;
	if (y == 0 && parsing->map[x][y] != '1')
		parsing->map_is_open = 1;
	if (x == parsing->nbr_lines && parsing->map[x][y] != '1')
		parsing->map_is_open = 1;
	if (y == parsing->longest_line && parsing->map[x][y] != '1')
		parsing->map_is_open = 1;
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

void	ft_free(char *newline, t_elems *elems)
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
	if (error_flag == 5)
		printf("Error : an element is incorrect.");
	ft_free(newline, elems);
	exit(0);
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

char 	*del_spaces(char *line)
{
	int i;
	char *newline;
	int j = 0;
	j++;

	i = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	newline = ft_strdup(line + i);
	if (!newline)
		return (NULL);
	return (newline);
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
	free(newline);
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

void	get_path(char *newline, int elem_flag, t_elems *elems)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	j = 0;
	i = 0;
	len = 0;
	if (elem_flag == 'S')
		i = 1;
	else
		i = 2;
	while ((newline[i] == ' ' || newline[i] == '	') && newline[i])
		i++;
	j = i;
	while (!(newline[j] == ' ' || newline[j] == '	') && newline[j])
	{
		j++;
		len++;
	}
	tmp = ft_strndup(newline, len, i);
	if (ft_strdup_path(tmp, elem_flag, elems) == 1)
	{
		free(tmp);
		error_elems(newline, elems, 0);
	}
	free(tmp);
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

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

static void		*ft_strfree(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0)
	{
		i--;
		free(str[i]);
	}
	free(str);
	return ((void *)0);
}

static int		ft_nbwrds(char const *s, char c)
{
	int	i;
	int	j;

	if (!s)
		return (-1);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (j);
}

static int		w(char const *s, int i, char c)
{
	while (s[i] != c && s[i])
		i++;
	return (i + 1);
}

char			**ft_split(char const *s, char c)
{
	char	**out;
	int		i[3];

	if ((ft_nbwrds(s, c) == -1)
			|| !(out = (char **)malloc(sizeof(char *) * (ft_nbwrds(s, c) + 1))))
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (s[i[0]])
	{
		if (s[i[0]] != c)
		{
			if (!(out[i[1]] = (char *)malloc(sizeof(char) * w(s, i[0], c))))
				return (ft_strfree(out));
			i[2] = 0;
			while (s[i[0]] != c && s[i[0]])
				out[i[1]][i[2]++] = s[i[0]++];
			out[i[1]][i[2]] = '\0';
			i[1]++;
		}
		else
			i[0]++;
	}
	out[i[1]] = NULL;
	return (out);
}

char			*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	len = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	len = ft_strlen(&s1[start]);
	if (len != 0)
		while (s1[start + len - 1] &&
				ft_strchr(set, s1[start + len - 1]) != NULL)
			len--;
	return (ft_substr(s1, start, len));
}

char	*ft_strtrim_inside(char *str)
{
	char	*strnew;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strnew = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!strnew)
	{
		free(str);
		return (NULL);
	}
	ft_bzero(strnew, ft_strlen(str));
	while (str[j])
	{
		if (str[j] != ' ' && str[j] != '	')
		{
			strnew[i] = str[j];
			i++;
		}
		j++;
	}
	strnew[i] = '\0';
	free(str);
	return (strnew);
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
	if (ft_strlen(final[0]) > 3 || ft_strlen(final[1]) > 3
	|| ft_strlen(final[2]) > 3 || i > 3)
	{
		free(final[0]);
		free(final[1]);
		error_elems(final[2], elems, 5);
	}
	color_code(final, elem_flag, elems);
}

void	stock_values(char *newline, int elem_flag, t_elems *elems)
{
	if (elem_flag == 'R')
		get_R_values(newline, elems);
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
	if (elem_flag == 'N' + 'O' || elem_flag == 'S' + 'O'
		|| elem_flag == 'W' + 'E' || elem_flag == 'E' + 'A'
		|| elem_flag == 'S')
	{
			get_path(newline, elem_flag, elems);
			free(newline);
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
	if (elems->R_is_present == TRUE && elems->NO_is_present == TRUE
		&& elems->SO_is_present == TRUE && elems->WE_is_present == TRUE
		&& elems->EA_is_present == TRUE && elems->S_is_present == TRUE
		&& elems->F_is_present == TRUE && elems->C_is_present == TRUE)
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
		{
			free(line);
			return ;
		}
		newline = del_spaces(line);
		if (newline == NULL)
				error_elems(line, elems, 0);
		free(line);
		elem_flag = wich_elem(newline, elems);
		check_flag(elem_flag, elems);
		if (elems->double_elem)
			error_elems(newline, elems, 1);
		stock_elem(newline, elem_flag, elems);
	}
}

/*void	pass_empty_lines(fd)
{
	char	*line;

	line = NULL;
	while ((get_next_line(fd, &line) == 1) && ft_strcmp(line, "\n") == 0)
	{
		if (!(ft_strcmp(line, "\n") == 0))
			return (line);
	}
	return (line);
}*/

void	parser(t_parsing *parsing, t_elems *elems)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open(parsing->filename, O_RDONLY);
	get_elems(fd, elems);
		if (check_all_elems(elems) == 1)
			error_elems(str, elems, 0);

	/*write(1, "PB", 1);
	find_map(fd, parsing);
	write(1, "a", 1);
	if (parsing->valid_map == NULL || parsing->map_error == TRUE)
		error_elems(line, elems, 4);
	fd = open(parsing->filename, O_RDONLY);
	get_map(fd, parsing);
	valid_map(parsing);
	parsing->valid_map = alloc_map(parsing->nbr_lines, parsing->longest_line);
	get_valid_map(parsing);
	*/
}