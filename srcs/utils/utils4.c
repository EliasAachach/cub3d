/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:41:30 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/04 17:41:52 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub3d.h"

int		res_check(char *str, t_elems *elems)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	elems->mlx_ptr = mlx_init();
	mlx_get_screen_size(elems->mlx_ptr, (&x), (&y));
	while(str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	if (elems->R_x_value <= 0 || elems->R_y_value <= 0)
		return (1);
	if (elems->R_x_value > x)
		elems->R_x_value = x;
	if (elems->R_y_value > y)
		elems->R_y_value = y;
	return (0);
}