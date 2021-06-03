#include "cub3d.h"

void	free_parsing(t_parsing *parsing)
{
	int	i;

	i = 0;
	if (parsing->first_line)
		free(parsing->first_line);
	if (parsing->map)
	{
		while (parsing->map[i])
		{
			free(parsing->map[i]);
			i++;
		}
		free(parsing->map);
	}
}

void	parse_error(t_parsing *parsing, t_elems *elems, int error_flag)
{
	if (error_flag == 0)
		printf("Error\nMap is invalid.");
	if (error_flag == 1)
		printf("Error\nMap is open.");
	free_parsing(parsing);
	error_elems(NULL, elems, 9);
	exit(0);
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
	char *line;

	line = NULL;
	while(get_next_line(elems->error_fd, &line) == 1)
		free(line);
	 free(line);
	if (error_flag == 0)
		printf("Error\nAn element is missing.");
	if (error_flag == 1)
		printf("Error\nAn element is present mutiple times.");
	if (error_flag == 3)
		printf("Error\nUnexpected error, check your map.");
	if (error_flag == 4)
		printf("Error\nMap is invalid.");
	if (error_flag == 5)
		printf("Error\nAn element is incorrect.");
	ft_free(newline, elems);
	exit(0);
}