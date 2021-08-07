#include "../../includes/cub3d.h"

void	free_parsing(t_parsing *parsing, t_ray *ray)
{
	int	i;

	i = 0;
	if (parsing->first_line)
		free(parsing->first_line);
	if (ray->map)
	{
		while (ray->map[i])
		{
			free(ray->map[i]);
			i++;
		}
		free(ray->map);
	}
}

void	parse_error(t_parsing *parsing, t_elems *elems, int error_flag,\
	t_ray *ray)
{
	if (error_flag == 0)
		printf("Error\nMap is invalid.");
	if (error_flag == 1)
		printf("Error\nMap is open.");
	free_parsing(parsing, ray);
	elems->err_flag = 9;
	error_elems(NULL, elems, ray);
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

void	free_texture(t_ray *ray)
{
	int i;

	i = 0;
	while (ray->img.addr[i])
	{
		if (ray->img.addr[i])
			mlx_destroy_image(ray->mlx.mlx_ptr, ray->img.addr[i]);
		i++;
	}
	if (ray->img.addr)
		free(ray->img.addr);
	if (ray->img.image)
		free(ray->img.image);
}

void	err_ptr(t_ray *ray, t_elems *elems)
{
	ray->err.NO = elems->path_to_NO;
	ray->err.SO = elems->path_to_SO;
	ray->err.WE = elems->path_to_WE;
	ray->err.EA = elems->path_to_EA;
}

void	error_mlx(t_ray *ray)
{
	int i;

	i = 0;
	if (ray->err.NO)
		free(ray->err.NO);
	if (ray->err.SO)
		free(ray->err.SO);
	if (ray->err.EA)
		free(ray->err.EA);
	if (ray->err.WE)
		free(ray->err.WE);
	free_texture(ray);
	if (ray->mlx.mlx_ptr)
	{
		mlx_destroy_display(ray->mlx.mlx_ptr);
		free(ray->mlx.mlx_ptr);
	}
	if (ray->map)
	{
		while (ray->map[i])
		{
			free(ray->map[i]);
			i++;
		}
		free(ray->map);
	}
	exit(0);
	// error_elems(NULL, elems, ray);
}

void	error_elems(char *newline, t_elems *elems, t_ray *ray)
{
	char	*line;

	line = NULL;
	while (get_next_line(elems->error_fd, &line) == 1)
		free(line);
	free(line);
	if (elems->err_flag != 6)
		mlx_destroy_display(ray->mlx.mlx_ptr);
	if (ray->mlx.mlx_ptr)
		free(ray->mlx.mlx_ptr);
	if (elems->err_flag == 0)
		printf("Error\nAn element is missing.");
	if (elems->err_flag == 1)
		printf("Error\nAn element is present mutiple times.");
	if (elems->err_flag == 3)
		printf("Error\nUnexpected error, check your map.");
	if (elems->err_flag == 4)
		printf("Error\nMap is invalid.");
	if (elems->err_flag == 5)
		printf("Error\nAn element is incorrect.");
	ft_free(newline, elems);
	exit(0);
}
