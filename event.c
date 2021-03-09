#include <mlx.h>
#include "./includes/cub3d.h"
#include <stdlib.h>

typedef struct  s_vars
{
    void    *mlx;
    void    *win;
}               t_vars;

int            close(int keycode, t_vars *vars)
{
    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}

int             main()
{
    t_vars vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello World !");
    mlx_hook(vars.win, 2, 1L<<0, close, &vars);
    mlx_loop(vars.mlx);
}