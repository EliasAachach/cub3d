#include "cub3d.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void    parser(t_parsing *parsing, t_elems *elems, char **arg, int nbr_arg);
void	ft_putstr_fd(char *s);

void	init_parsing(t_parsing *parsing, t_elems *elems)
{
    parsing->filename = NULL;
	parsing->first_line = NULL;
	parsing->map = NULL;
	parsing->valid_map = NULL;
    parsing->longest_line = 0;
	parsing->nbr_lines = 0;
	parsing->player_x = 0;
	parsing->player_y = 0;
	parsing->player_exists = 0;
	parsing->highest_x = 0;
	parsing->lowest_x = 0;
	parsing->highest_y = 0;
	parsing->lowest_y = 0;
	parsing->map_is_open = 0;
	parsing->map_error = 0;
	parsing->player_in_map = 0;
	parsing->first_line_passed = 0;

	elems->R_is_present = 0;
	elems->NO_is_present = 0;
	elems->SO_is_present = 0;
	elems->WE_is_present = 0;
	elems->EA_is_present = 0;
	elems->S_is_present = 0;
	elems->F_is_present = 0;
	elems->C_is_present = 0;
	elems->missing_elem = 0;
	elems->double_elem = 0;
	elems->R_x_value = 0;
	elems->R_y_value = 0;
	elems->r_F = 0;
	elems->g_F = 0;
	elems->b_F = 0;
	elems->r_C = 0;
	elems->g_C = 0;
	elems->b_C = 0;
	elems->error_fd = 0;
	elems->path_to_S = NULL;
	elems->path_to_NO = NULL;
	elems->path_to_SO = NULL;
	elems->path_to_EA = NULL;
	elems->path_to_WE = NULL;
}

int     main(int argc, char **argv)
{
    t_parsing	parsing;
    t_elems		elems;
    init_parsing(&parsing, &elems);
    parser(&parsing, &elems, argv, argc);
	printf("path_to_S : %s\n", elems.path_to_S);
	printf("path_to_NO : %s\n", elems.path_to_NO);
	printf("path_to_SO : %s\n", elems.path_to_SO);
	printf("path_to_EA : %s\n", elems.path_to_EA);
	printf("path_to_WE : %s\n", elems.path_to_WE);
	printf("Rx : %d\n", elems.R_x_value);
	printf("Ry : %d\n", elems.R_y_value);
	printf("rF : %d\n", elems.r_F);
	printf("gF : %d\n", elems.g_F);
	printf("bF : %d\n", elems.b_F);
	printf("rC : %d\n", elems.r_C);
	printf("gC : %d\n", elems.g_C);
	printf("bC : %d\n", elems.b_C);
		int i = 0;
	while (i <= parsing.nbr_lines)
	{
		ft_putstr_fd(parsing.map[i]);
		ft_putstr_fd("\n");
		i++;
	}
	i = 0;
	while (i <= parsing.nbr_lines)
	{
		free(parsing.map[i]);
		i++;
	}
	free(parsing.valid_map);
	free(elems.path_to_S);
	free(elems.path_to_NO);
	free(elems.path_to_SO);
	free(elems.path_to_EA);
	free(elems.path_to_WE);
	// system("leaks a.out");
}