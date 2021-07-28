#include <mlx.h>
#include "./includes/cub3d.h"
#include <stdlib.h>

typedef struct  s_vars
{
    void    *mlx;
    void    *win;
}               t_vars;

typedef struct  s_colors
{
    int     r;
    int     g;
    int     b;
    int     a;
}               t_colors;

int            close(int keycode, t_vars *vars)
{
    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}

void            my_mlx_pixel_put(char *data, int x, int y, t_colors colors)
{
    data[(y * 640 + x) * 4 + RGB_R] = colors.r;
    data[(y * 640 + x) * 4 + RGB_G] = colors.g;
    data[(y * 640 + x) * 4 + RGB_B] = colors.b;
}

int             main()
{
    t_colors colors;
    t_vars vars;
    void    *addr;
    char    *mlx_img;
    void    *img;
    int     bpp;
    int     size;
    int     endian;
    int     imgx;
    int     imgy;
    int     x;
    int     y;
    char    *fond;

    y = 0;
    colors.r = 127;
    colors.g = 127;
    colors.b = 127;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Dogo");
    mlx_hook(vars.win, 2, 1L<<0, close, &vars);
    addr = mlx_xpm_file_to_image(vars.mlx, "./dogo.xpm", &imgx, &imgy);
    img = mlx_new_image(vars.mlx, 640, 480);
    fond = mlx_get_data_addr(img, &bpp, &size, &endian);
    my_mlx_pixel_put(fond, 0, 0, colors);
    while (y <= 480)
    {
        x = 0;
        while (x <= 320)
        {
            my_mlx_pixel_put(fond, x, y, colors);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(vars.mlx, vars.win, img, 0, 0);
    mlx_put_image_to_window(vars.mlx, vars.win, addr, 150, 50);
    mlx_loop(vars.mlx);
}
