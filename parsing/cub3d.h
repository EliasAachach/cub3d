//clang rainbow.c -o rainbow -lmlx -lXext -lX11 -lm
#ifndef _CUB3D_H_
# define _CUB3D_H_
//BOOL
# define TRUE 1
# define FALSE 0
//end_BOOL
//keys
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
//end_keys
//
//RGB_macros
# define RGB_A 3
# define RGB_R 2
# define RGB_G 1
# define RGB_B 0
//end_RGB_macrosx
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct	s_elems
{
	int			R_is_present;
	int			NO_is_present;
	int			SO_is_present;
	int			WE_is_present;
	int			EA_is_present;
	int			S_is_present;
	int			F_is_present;
	int			C_is_present;
	int			missing_elem;	//si err ds elems
	int			double_elem;	//si deux fois le meme elems
	int			R_x_value;
	int			R_y_value;
	int			r_F;
	int			g_F;
	int			b_F;
	int			r_C;
	int			g_C;
	int			b_C;
	char		*path_to_S;
	char		*path_to_NO;
	char		*path_to_SO;
	char		*path_to_EA;
	char		*path_to_WE;
}				t_elems;

typedef struct	s_parsing
{
	int		longest_line;
	int		nbr_lines;
	int		player_x;
	int		player_y;
	int		player_exists;
	int		highest_x;
	int		lowest_x;
	int		highest_y;
	int		lowest_y;
	int		map_is_open;
	int		map_error;
	char	*filename;
	char	*first_line;
	char	**map;
	char	**valid_map;
}				t_parsing;

#endif