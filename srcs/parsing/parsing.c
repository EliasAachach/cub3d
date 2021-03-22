#include "get_next_line.h"
#include "cub3d.h"
#include  <unistd.h>

char	**alloc_map(char **map, int nbr_lines, int line_len)
{
	int i;

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

char	**find_map(int fd, ); //params : le fd deja ouvert pour les 1ers elements
{
	char 	**map;
	char 	*line;
    int		nbr_lines;
	int		line_len;

	line = NULL;
    nbr_lines = 0;
	line_len = 0;
    while (get_next_line(fd, &line) == 1)
    {
		if (line[0] == '\n')
		{
			return (NULL);
		}
		if (line_len < ft_strlen(line))
			line_len = ft_strlen(line);
        free(line);
		nbr_lines++;
	}
    free(line);
	map = alloc_map(map, nbr_lines, line_len);
    if (!map)
		return (NULL);
	close (fd);
	return (map);
}

int	is_player(char c)
{
	if ( c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

char	**

char	**valid_map(char **map)
{
	int x;
	int y;
	int player_in_map;
	char **valid_map;

	player_in_map = FALSE;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (is_player(map[x][y]) == 1)
			{
				FLOOD_FILL
			}
			y++;
		}
		x++;
	}
}