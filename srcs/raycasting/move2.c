/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:42:08 by user42            #+#    #+#             */
/*   Updated: 2021/07/28 19:10:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    rot_left(t_ray *ray)
{
	ray->olddirx = ray->dirx;
	ray->dirx = ray->dirx * cos(ray->mv.rotspeed) -\
					ray->diry * sin(ray->mv.rotspeed);
	ray->diry = ray->olddirx * sin(ray->mv.rotspeed) +\
					ray->diry * cos(ray->mv.rotspeed);
	ray->oldplanx = ray->planx;
	ray->planx = ray->planx * cos(ray->mv.rotspeed) -\
					ray->plany * sin(ray->mv.rotspeed);
	ray->plany = ray->oldplanx * sin(ray->mv.rotspeed) +\
					ray->plany * cos(ray->mv.rotspeed);
}

void    rot_right(t_ray *ray)
{
	ray->olddirx = ray->dirx;
	ray->dirx = ray->dirx * cos(-ray->mv.rotspeed) -\
					ray->diry * sin(-ray->mv.rotspeed);
	ray->diry = ray->olddirx * sin(-ray->mv.rotspeed) +\
					ray->diry * cos(-ray->mv.rotspeed);
	ray->oldplanx = ray->planx;
	ray->planx = ray->planx * cos(-ray->mv.rotspeed) -\
					ray->plany * sin(-ray->mv.rotspeed);
	ray->plany = ray->oldplanx * sin(-ray->mv.rotspeed) +\
					ray->plany * cos(-ray->mv.rotspeed);
}