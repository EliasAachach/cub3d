/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:18:15 by user42            #+#    #+#             */
/*   Updated: 2021/08/13 10:44:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int key, t_ray *ray)
{
	if (key == ESC_KEY)
		win_close(ray);
	if (key == W_KEY)
		ray->mv.w = 1;
	if (key == A_KEY)
		ray->mv.a = 1;
	if (key == S_KEY)
		ray->mv.s = 1;
	if (key == D_KEY)
		ray->mv.d = 1;
	if (key == LEFT_KEY)
		ray->mv.left = 1;
	if (key == RIGHT_KEY)
		ray->mv.right = 1;
	loop(ray);
	return (0);
}

int	key_leave(t_ray *ray)
{
	win_close(ray);
	return (0);
}

int	key_released(int key, t_ray *ray)
{
	if (key == ESC_KEY)
		win_close(ray);
	if (key == W_KEY)
		ray->mv.w = 0;
	if (key == A_KEY)
		ray->mv.a = 0;
	if (key == S_KEY)
		ray->mv.s = 0;
	if (key == D_KEY)
		ray->mv.d = 0;
	if (key == LEFT_KEY)
		ray->mv.left = 0;
	if (key == RIGHT_KEY)
		ray->mv.right = 0;
	loop(ray);
	return (0);
}
