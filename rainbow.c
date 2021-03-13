#include <mlx.h>
#include "./includes/cub3d.h"
#include <stdlib.h>

typedef struct  s_colors
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *fond;
    int     r;
    int     g;
    int     b;
    int     a;
}               t_colors;

int             set_colors(int keycode, t_colors *colors)
{
    if (keycode == R_KEY)
    {
        if (colors->r == 255)
            colors->r = 0;
        else
            colors->r += 15;
    }
    if (keycode == G_KEY)
    {
        if (colors->g == 255)
            colors->g = 0;
        else
            colors->g += 15;
    }
    if (keycode == B_KEY)
    {
        if (colors->b == 255)
            colors->b = 0;
        else
            colors->b += 15;
	}
    return (0);
}

int            close(int keycode, t_colors *colors)
{
    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(colors->mlx, colors->win);
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

int     render_next_frame(t_colors *colors)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y <= 480)
    {
        x = 0;
        while (x <= 640)
        {
            my_mlx_pixel_put(colors->fond, x, y, *colors);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(colors->mlx, colors->win, colors->img, 0, 0);
    return (1);
}

int             main()
{
    t_colors colors;
    void    *addr;
    char    *mlx_img;
    int     bpp;
    int     size;
    int     endian;
    int     imgx;
    int     imgy;
    int     x;
    int     y;

    y = 0;
    colors.r = 0;
    colors.g = 0;
    colors.b = 255;
    colors.mlx = mlx_init();
    colors.win = mlx_new_window(colors.mlx, 640, 480, "Rainbow");
    mlx_hook(colors.win, 2, 1L<<0, close, &colors);
    mlx_hook(colors.win, 2, 1L<<0, set_colors, &colors);
    colors.img = mlx_new_image(colors.mlx, 640, 480);
    colors.fond = mlx_get_data_addr(colors.img, &bpp, &size, &endian);
    mlx_loop_hook(colors.mlx, render_next_frame, &colors);
    mlx_loop(colors.mlx);
}