#include "../../includes/cub3d.h"

void    mv_frwrd(t_ray *ray)
{
	if (ray->map[(int)(ray->posx + ray->dirx * ray->mv.speed)]\
		[(int)ray->posy] == '0')
		ray->posx += ray->dirx * ray->mv.speed;
	if (ray->map[(int)ray->posx]\
		[(int)(ray->posy + ray->diry * ray->mv.speed)] == '0')
		ray->posy += ray->diry * ray->mv.speed;
}

void    mv_dwnwrd(t_ray *ray)
{
    if (ray->map[(int)(ray->posx - ray->dirx * ray->mv.speed)][(int)ray->posy]\
        == '0')
        ray->posx -= ray->dirx * ray->mv.speed;
    if (ray->map[(int)ray->posx][(int)(ray->posy - ray->diry * ray->mv.speed)]\
        == '0')
        ray->posy -= ray->diry * ray->mv.speed;
}

void    mv_left(t_ray *ray)
{
    if (ray->map[(int)(ray->posx - ray->planx * ray->mv.speed)][(int)ray->posy]\
        == '0')
        ray->posx -= ray->planx * ray->mv.speed;
    if (ray->map[(int)ray->posx][(int)(ray->posy - ray->plany * ray->mv.speed)]\
        == '0')
        ray->posy -= ray->plany * ray->mv.speed;
}

void    mv_right(t_ray *ray)
{
    if (ray->map[(int)(ray->posx + ray->planx * ray->mv.speed)][(int)ray->posy]\
        == '0')
        ray->posx += ray->planx * ray->mv.speed;
    if (ray->map[(int)ray->posx][(int)(ray->posy + ray->plany * ray->mv.speed)]\
        == '0')
        ray->posy += ray->plany * ray->mv.speed;
}