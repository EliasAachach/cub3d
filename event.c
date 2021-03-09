
#include <mlx.h>

typedef struct  s_vars
{
    void    *mlx;
    void    *win;
}               t_vars;

void            close(int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
}

int             main()
{
    t_vars vars;

    vars.mlx = init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello World !");
    mlx_hook(vars.win, 2, 1L<<0, close, &vars);
    mlx_loop(vars.mlx);
}