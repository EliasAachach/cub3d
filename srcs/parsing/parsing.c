#include "get_next_line.h"
#include "cub3d.h"
#include  <unistd.h>

char	**alloc_map(char **map, int nbr_lines, int line_len)
{
	int i;
	i = 0;
	while (i <= nbr_lines)
	{
		map[i] = ((char *)malloc(sizeof(char) * (line_len + 1)));
		if (!map[i])
			return (NULL);
		i++;
	}
	retrun (map);
}

char	**find_map();
{
	char 	**map;
	char 	*line;
	int		fd;
    int		nbr_lines;
	int		line_len;

	line = NULL;
	fd = open ("cub3d.map", 0_RDONLY);
    nbr_lines = 0;
	line_len = 0;
    while (get_next_line(fd, line) == 1)
    {
		if (line_len < ft_strlen(line))
			line_len = ft_strlen(line);
		nbr_lines++;
	}
	map = alloc_map(map, nbr_lines, line_len);
	return (map);
}