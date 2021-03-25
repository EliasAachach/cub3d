#include "get_next_line.h"
#include "cub3d.h"
#include  <unistd.h>

char	**alloc_map(int nbr_lines, int longest_line)
{
	int		i;
	char	*map

	i = 0;
	map = ((char *)malloc(sizeof(char) * (nbr_lines +1)));
    if (!map)
        return (NULL);
	while (i <= nbr_lines)
	{
		map[i] = ((char *)malloc(sizeof(char) * (line_len + 1)));
		if (!map[i])
			return (NULL);
		i++;
	}
	return (map);
}

char	**find_map(int fd, t_parsing *parsing); //params : le fd deja ouvert pour les 1ers elements
{
	char	*line;

	parsing->longest_line = 0;
	line = NULL;
    parsing->nbr_lines = 0;
	if (get_next_line(fd, &line) == 1)
	{
		parsing->first_line = ft_strdup(line)
		// on recupere la premiere ligne de la map
		if (parsing->longest_line > ft_strlen(line))

	}
    while (get_next_line(fd, &line) == 1)
    {
		if (line[0] == '\n')
		{
			//LIGNE VIDE DANS LA MAP
			parsing.valid_map = NULL;
			return;
		}
		if (parsing->longest_line < ft_strlen(line))
			parsing->longest_line = ft_strlen(line);
        free(line);
		parsing->nbr_lines++;
	}
    free(line);
	parsing->map = alloc_map(parsing->nbr_lines, parsing->longest_line);
    if (!parsing->map)
		return (NULL);
	close (fd);
	return (parsing->map);
}

int	player_in_map(char c)
{
	if ( c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

char **get_map(int fd, t_parsing *parsing)
{
	int		x;
	int		first_line_passed;
	char	*line;

	first_line_passed = FALSE
	line = NULL;
	while (get_next_line(fd, &line) == 1 && first_line_passed == FALSE)
	{
		if (ft_strcmp(line, first_line) == 0)
		{
			parsing->map[x]ft_strdup(line);
			x++;
			while (get_next_line(fd, &line) == 1 && x <= parsing->nbr_lines)
			{
				parsing->map[x] = ft_strdup(line);
				x++;
			}
		}
		first_line_passed = TRUE
	}
}

void	flood_fill(t_parsing *parsing, int x, int y)
{
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
	if (parsing->map[x][y] == '0')
	{
		parsing->map[x][y] == -1;
		flood_fill(&parsing, x, y + 1);
		flood_fill(&parsing, x, y - 1);
		flood_fill(&parsing, x + 1, y);
		flood_fill(&parsing, x - 1, y);
	}
}

char	**valid_map(t_parsing *parsing)
{
	int	x;
	int	++y;

	x = 0;
	while (parsing->map[x])
	{
		y = 0;
		while (parsing->map[x][y])
		{
			if (player_in_map(parsing->map[x][y]) == 1)
			{
				if (parsing->player_exists == TRUE)
				{
					//plus d'un joueur dans la map->erreur
					return (NULL);
				}
				parsing->player_in_map = TRUE;
				parsing->player_x = parsing->lowest_x;
				parsing->player_y = parsing->lowest_y;
				parsing->player_x = x;
				parsing->player_y = y;
				flood_fill(&parsing, x, y);
			}
			y++;
		}
		x++;
	}
}

char **parsing()
{
	int		fd;
	char	*line;
	t_parsing parsing;

	parsing.longest_line = 0;
	parsing.nbr_lines = 0;
	parsing.player_x = 0;
	parsing.player_y = 0;
	//parser les 1er elements

	//parser la map
	find_map(fd, &parsing);
	fd = open (parsing.map, 0_RDONLY);
	get_map(fd, &parsing);
	valid_map(&parsing);
	if (parsing.valid_map == NULL)
	{
		//erreur dans la map;
	}
	get_valid_map(&parsing);
}