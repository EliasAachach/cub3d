/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:43:00 by user42            #+#    #+#             */
/*   Updated: 2021/08/08 19:49:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_parsing	parsing;
	t_elems		elems;
	t_ray		ray;

	init_parsing(&parsing, &elems, argc, &ray);
	parser(&parsing, &elems, &ray, argv);
	init_var(&ray, &elems);
	raycasting(&parsing, &elems, &ray);
}
