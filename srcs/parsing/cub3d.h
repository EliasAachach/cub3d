/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 13:54:05 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/28 11:22:31 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TRUE 1
# define FALSE 0

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define R_KEY 114
# define G_KEY 103
# define B_KEY 98
# define RIGHT_KEY 65363
# define LEFT_KEY 65361
# define ESC_KEY 65307

# define RGB_A 3
# define RGB_R 2
# define RGB_G 1
# define RGB_B 0

# define X_WALL 0
# define Y_WALL 1

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "gnl/get_next_line.h"
# include <mlx.h>

typedef struct s_elems
{
	void		**img_ptr;
	void		*mlx_win;
	void		*mlx_ptr;
	int			R_is_present;
	int			NO_is_present;
	int			SO_is_present;
	int			WE_is_present;
	int			EA_is_present;
	int			S_is_present;
	int			F_is_present;
	int			C_is_present;
	int			missing_elem;
	int			double_elem;
	int			R_x_value;
	int			R_y_value;
	int			r_F;
	int			g_F;
	int			b_F;
	int			r_C;
	int			g_C;
	int			b_C;
	int			error_fd;
	char		*path_to_S;
	char		*path_to_NO;
	char		*path_to_SO;
	char		*path_to_EA;
	char		*path_to_WE;
	char		*last_elem_line;
}				t_elems;

typedef struct s_parsing
{
	int		longest_line;
	int		nbr_lines;
	int		player_x;
	int		player_y;
	int		player_dir;
	int		player_exists;
	int		highest_x;
	int		lowest_x;
	int		highest_y;
	int		lowest_y;
	int		map_is_open;
	int		map_error;
	int		nbr_lines_map;
	int		first_line_passed;
	int		player_in_map;
	char	*filename;
	char	*first_line;
	char	**map;
	char	**valid_map;
}				t_parsing;

typedef	struct s_dda
{
	int		mapx;
	int		mapy;
	double	stepx;
	double	stepy;
	int		side;
	int		hit;
}				t_dda;

typedef	struct s_draw
{
	int		line_height;
	int		start_draw;
	int		end_draw;
}				t_draw;

typedef struct s_colors
{
	int	r;
	int	g;
	int	b;
	int	a;
}				t_colors;

typedef struct s_mlx
{
	void	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		endian;
	int		size;
}				t_mlx;

typedef struct s_ray
{
	t_mlx		mlx;
	t_dda		dda;
	t_draw		draw;
	t_colors	roof;
	t_colors	wall;
	t_colors	floor;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		ray_dirx;
	double		ray_diry;
	double		planx;
	double		plany;
	double		camerax;
	double		side_distx;
	double		side_disty;
	double		delta_distx;
	double		delta_disty;
	double		resx;
	double		resy;
	double		perp_wall_dist;
}				t_ray;

char	*ft_strdup(char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);
void	flood_fill(t_parsing *parsing, char **ff_map, int x, int y);
int		player_in_map(char c, t_parsing *parsing);
void	parse_error(t_parsing *parsing, t_elems *elems, int error_flag);
void	error_elems(char *newline, t_elems *elems, int error_flag);
void	get_path(char *newline, int elem_flag, t_elems *elems);
void	get_elems(int fd, t_elems *elems);
void	check_flag(int elem_flag, t_elems *elems);
char	*del_spaces(char *line);
void	get_R_values(char *newline, t_elems *elems);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strtrim_inside(char *str);
char	**ft_split(char const *s, char c);
void	*ft_strfree(char **str);
void	stock_values(char *newline, int elem_flag, t_elems *elems);
int		wich_elem(char *line, t_elems *elems);
int		res_check(char *str, t_elems *elems);
void	find_map(int fd, t_parsing *parsing);
int		is_first_line(char *line);
int		check_line(char *line);
char	**alloc_map(int nbr_lines, int longest_line);
char	*del_spaces(char *line);
void	valid_map(t_parsing *parsing);
int		rgb_check(t_elems *elems);
void	arg_check(char **arg, int nbr_arg);
int		check_all_elems(t_elems *elems);
void	check_colors(char *newline, int elem_flag, t_elems *elems, int i);
int		final_check(char **final, int i);
void    raycasting(t_parsing *parsing, t_elems *elems, t_ray *ray);

#endif