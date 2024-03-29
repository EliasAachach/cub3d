/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 13:54:05 by elaachac          #+#    #+#             */
/*   Updated: 2021/08/19 14:14:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TRUE 1
# define FALSE 0

# define KEYPRESS 2
# define KEYRELEASE 3

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

# define TEXWIDTH 64
# define TEXHEIGHT 64

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../srcs/parsing/gnl/get_next_line.h"
# include "mlx.h"

typedef struct s_elems
{
	int					R_is_present;
	int					NO_is_present;
	int					SO_is_present;
	int					WE_is_present;
	int					EA_is_present;
	int					S_is_present;
	int					F_is_present;
	int					C_is_present;
	int					missing_elem;
	int					double_elem;
	int					err_flag;
	int					R_x_value;
	int					R_y_value;
	int					r_F;
	int					g_F;
	int					b_F;
	int					r_C;
	int					g_C;
	int					b_C;
	int					error_fd;
	int					elem_flag;
	int					flag_elem;
	unsigned long int	x_atoul;
	unsigned long int	y_atoul;
	char				*path_to_S;
	char				*path_to_NO;
	char				*path_to_SO;
	char				*path_to_EA;
	char				*path_to_WE;
	char				*last_elem_line;
}				t_elems;

typedef struct s_parsing
{
	int		nbr_arg;
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
	char	**valid_map;
}				t_parsing;

typedef struct s_tex
{
	int			num;
	double		wallx;
	double		pos;
	int			x;
	int			y;
	double		step;
}				t_tex;

typedef struct s_dda
{
	int		mapx;
	int		mapy;
	double	stepx;
	double	stepy;
	int		side;
	int		hit;
}				t_dda;

typedef struct s_draw
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
	void	*mlx_ptr;
	void	*mlx_win;
	char	*data_addr;
	int		bpp;
	int		endian;
	int		size;
	int		x;
	int		y;
}				t_mlx;

typedef struct s_mv
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
	double	speed;
	double	rotspeed;
}				t_mv;

typedef struct s_img
{
	void	**addr;
	char	**image;
	int		height;
	int		width;
	int		endian;
	int		bpp;
	int		s_line;
}				t_img;

typedef struct s_err
{
	char	*NO;
	char	*SO;
	char	*EA;
	char	*WE;
	char	*S;
}				t_err;

typedef struct s_ray
{
	t_mv		mv;
	t_mlx		mlx;
	t_dda		dda;
	t_img		img;
	t_tex		tex;
	t_err		err;
	t_draw		draw;
	t_colors	roof;
	t_colors	wall;
	t_colors	floor;
	char		**map;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		olddirx;
	double		olddiry;
	double		planx;
	double		plany;
	double		oldplanx;
	double		oldplany;
	double		ray_dirx;
	double		ray_diry;
	double		camerax;
	double		side_distx;
	double		side_disty;
	double		delta_distx;
	double		delta_disty;
	double		resx;
	double		resy;
	double		perp_wall_dist;
}				t_ray;

void				ft_putstr_fd(char *s);
int					ft_strcmp(char *s1, char *s2);
int					ft_atoi(const char *str);
int					player_in_map(char c, t_parsing *parsing);
int					wich_elem(char *line, t_elems *elems, t_ray *ray);
int					res_check(char *str, t_elems *elems, t_ray *ray);
int					is_first_line(char *line);
int					check_line(char *line);
int					rgb_check(t_elems *elems);
int					final_check(char **final, int i);
int					key_pressed(int key, t_ray *ray);
int					key_released(int key, t_ray *ray);
int					win_close(t_ray *ray);
int					loop(t_ray *ray);
int					key_leave(t_ray *ray);
int					check_all_elems(t_elems *elems);
int					elem_present(t_elems *elems);
char				*ft_strdup(char *s);
char				*del_spaces(char *line);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_strtrim_inside(char *str);
char				**ft_split(char const *s, char c);
char				**alloc_map(int nbr_lines, int longest_line);
char				*del_spaces(char *line);
void				elem_found(t_elems *elems, t_ray *ray, char *newline, \
						int elem_flag);
void				flood_fill(t_parsing *parsing, char **ff_map, int x, int y);
void				parse_error(t_parsing *parsing, t_elems *elems, \
						int error_flag, t_ray *ray);
void				error_elems(char *newline, t_elems *elems, t_ray *ray);
void				get_path(char *newline, int elem_flag, t_elems *elems, \
						t_ray *ray);
void				get_elems(int fd, t_elems *elems, t_ray *ray);
void				init_get_elems(int *elem_flag, t_elems *elems);
void				get_elems_2(char *newline, char *line, t_elems *elems, \
						t_ray *ray);
void				check_flag(int elem_flag, t_elems *elems);
void				get_R_values(char *newline, t_elems *elems, t_ray *ray);
void				*ft_strfree(char **str);
void				stock_values(char *newline, int elem_flag, t_elems *elems, \
						t_ray *ray);
void				valid_map(t_parsing *parsing, t_ray *ray);
void				find_map(int fd, t_parsing *parsing, t_ray *ray);
void				arg_check(char **arg, int nbr_arg, t_ray *ray);
void				check_colors(char *newline, int elem_flag, t_elems *elems, \
						int i);
void				raycasting(t_parsing *parsing, t_elems *elems, t_ray *ray);
void				parser(t_parsing *parsing, t_elems *elems, t_ray *ray, \
						char **arg);
void				mv_frwrd(t_ray *ray);
void				mv_dwnwrd(t_ray *ray);
void				mv_left(t_ray *ray);
void				mv_right(t_ray *ray);
void				init_var(t_ray *ray, t_elems *elems);
void				set_dir_plan(int player_dir, t_ray *ray);
void				rot_left(t_ray *ray);
void				rot_right(t_ray *ray);
void				error_mlx(t_ray *ray, int error_malloc);
void				err_ptr(t_ray *ray, t_elems *elems);
void				free_texture(t_ray *ray);
void				init_texture(t_ray *ray, t_elems *elems);
void				set_texture(t_ray *ray, t_elems *elems);
void				fill_img(t_ray *ray, int x);
void				colorpix(int x, int y, t_ray *ray, t_colors color);
void				data_draw(t_ray *ray);
void				init_image(t_ray *ray);
void				put_window(void *mlx_ptr, void *win_ptr, void *img);
void				dda(t_ray *ray);
void				set_step_sidedist(t_ray *ray);
void				set_dir_plan(int player_dir, t_ray *ray);
void				ft_free(char *newline, t_elems *elems);
void				init_parsing(t_parsing *parsing, t_elems *elems, int argc, \
						t_ray *ray);
unsigned long int	ft_atoul(char *str);

#endif
