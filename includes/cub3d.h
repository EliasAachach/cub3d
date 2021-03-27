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
//end_RGB_macros

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
	char	*first_line;
	char	**map;
	char	**valid_map;
}				t_parsing;

#endif