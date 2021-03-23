#include "get_next_line.h"
#include "cub3d.h"
#include  <unistd.h>

char	**alloc_map(char **parsing.map, int nbr_lines, int line_len)
{
	int i;

	i = 0;
    parsing.map = ((char *)malloc(sizeof(char) * (nbr_lines +1)));
    if (!parsing.map)
        return (NULL);
	while (i <= nbr_lines)
	{
		parsing.map[i] = ((char *)malloc(sizeof(char) * (line_len + 1)));
		if (!parsing.map[i])
			return (NULL);
		i++;
	}
	return (parsing.map);
}

char	**find_map(int fd, t_parsing *parsing); //params : le fd deja ouvert pour les 1ers elements
{
	char 	*line;
    int		nbr_lines;
	int		line_len;

	parsing->longest_line = NULL;
	line = NULL;
    nbr_lines = 0;
	line_len = 0;
    while (get_next_line(fd, &line) == 1)
    {
		if (line[0] == '\n')
		{
			//LIGNE VIDE DANS LA MAP
			return (NULL);
		}
		if (ft_strlen(parsing->longest_line) < ft_strlen(line))
		{
			if (parsing->longest_line)
				free(parsing->longest_line);
			parsing->longest_line = ft_strdup(line);
		}
        free(line);
		nbr_lines++;
	}
    free(line);
	parsing->map = alloc_map(parsing->map, nbr_lines, line_len);
    if (!parsing->map)
		return (NULL);
	close (fd);
	return (parsing->map);
}

int	is_player(char c)
{
	if ( c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}



char	**valid_map(t_parsing *parsing)
{
	int x;
	int y;
	int player_in_map;
	char **valid_map;

	player_in_map = FALSE;
	x = 0;
	while (parsing->map[x])
	{
		y = 0;
		while (parsing->map[x][y])
		{
			if (is_player(parsing->map[x][y]) == 1)
			{
				FLOOD_FILL
			}
			y++;
		}
		x++;
	}
}

char **parsing()
{
	int fd;
	char *line;
	t_parsing parsing;
	//parser les 1er elements

	//parser la map
	find_map(fd, &parsing);
	fd = open (parsing.map, 0_RDONLY);
	get_map(fd, &parsing);
	valid_map(&parsing);
}