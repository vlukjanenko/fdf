/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:27:24 by majosue           #+#    #+#             */
/*   Updated: 2020/01/14 12:21:11 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

void cleanarr(char ***array)
{
	char **tmp;

	tmp = *array;
	while (*(*array))
	{
		free(*(*array));
		(*array)++;
	}
	free(tmp);
}

int ft_close(t_mlx *mlx)
{
	//mlx
	//mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	//mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	//free(mlx->map);
	exit(0);
}

void ft_log_to_win(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i < mlx->n)
	{
		mlx->map[i].x = mlx->map[i].xp + WIN_WIDTH / 2;
		mlx->map[i].y = mlx->map[i].yp + WIN_HEIGHT / 2;
	}
}

void ft_win_to_log(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i <= mlx->n)
	{
		mlx->map[i].xi = mlx->map[i].xi - mlx->map[mlx->n].xi;
		mlx->map[i].yi = mlx->map[i].yi - mlx->map[mlx->n].yi;
	}
}

int ft_pr1(t_mlx *mlx)
{
	int i;
	double k;

	k = 1000;
	i = -1;
	while (++i < mlx->n)
	{
		mlx->map[i].xp = mlx->map[i].xo / (mlx->map[i].zo / k + 1);
		mlx->map[i].yp = mlx->map[i].yo / (mlx->map[i].zo / k + 1);
	}
	ft_log_to_win(mlx);
	return (1);
}
int ft_transform(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i < mlx->n)
	{
		
		/* mlx->map[i].xo = mlx->map[i].xi * cos(mlx->az) - mlx->map[i].yi * sin(mlx->az);
		mlx->map[i].yo = mlx->map[i].xi * sin(mlx->az) + mlx->map[i].yi * cos(mlx->az);
		mlx->map[i].zo = mlx->map[i].zi;
		mlx->map[i].yo = mlx->map[i].yo * cos(mlx->ax) + mlx->map[i].zo * sin(mlx->ax);
		mlx->map[i].zo = -mlx->map[i].yo * sin(mlx->ax) + mlx->map[i].zo * cos(mlx->ax);
		mlx->map[i].xo = mlx->map[i].xo * cos(mlx->ay) - mlx->map[i].zo * sin(mlx->ay);
		mlx->map[i].zo = mlx->map[i].xo * sin(mlx->ay) + mlx->map[i].zo * cos(mlx->ay);
		mlx->map[i].xo *= mlx->zoom;
		mlx->map[i].yo *= mlx->zoom;
		mlx->map[i].zo *= mlx->zoom;
		mlx->map[i].xo += mlx->map[mlx->n].xi;
		mlx->map[i].yo += mlx->map[mlx->n].yi; */
		mlx->map[i].xo = mlx->map[i].xi * cos(mlx->ay) * cos(mlx->az)  +  mlx->map[i].yi * (sin(mlx->ay)*sin(mlx->ax) - cos(mlx->ay) * sin(mlx->az)* cos(mlx->ax)) + mlx->map[i].zi * (cos(mlx->ay)* sin(mlx->az) * sin(mlx->ax) + sin(mlx->ay) * cos(mlx->ax));
		mlx->map[i].yo = mlx->map[i].xi * sin(mlx->az) + mlx->map[i].yi * cos(mlx->az) * cos(mlx->ax) - mlx->map[i].zi * cos(mlx->az) * sin(mlx->ax);
		mlx->map[i].zo = -mlx->map[i].xi * sin(mlx->ay) * cos(mlx->az) + mlx->map[i].yi * ( sin(mlx->ay)* sin(mlx->az) * cos(mlx->ax) + cos(mlx->ay) * sin(mlx->ax)) + mlx->map[i].zi * (cos(mlx->ay)*cos(mlx->ax) - sin(mlx->ay) * sin(mlx->az) *sin(mlx->ax));
		mlx->map[i].xo *= mlx->zoom;
		mlx->map[i].yo *= mlx->zoom;
		mlx->map[i].zo *= mlx->zoom;
		mlx->map[i].xo += mlx->map[mlx->n].xi;
		mlx->map[i].yo += mlx->map[mlx->n].yi;
	}
	return (1);
}

int ft_draw(t_mlx *mlx)
{
	int m;
	int i;

	i = -1;
	mlx_clear_window(mlx->mlx_ptr, mlx->win);
	m = WIN_WIDTH * WIN_HEIGHT;
	while (++i < m)
		mlx->img.data[i] = 0;
	ft_transform(mlx);
	ft_pr1(mlx);
	i = -1;
	while (++i < mlx->n)
	{
		if (i % mlx->w && i > 0)
			ft_draw_line(mlx, mlx->map[i], mlx->map[i - 1]);
		if (i / mlx->w)
			ft_draw_line(mlx, mlx->map[i], mlx->map[i - mlx->w]);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (1);
}

int ft_move(int key, t_mlx *mlx, int x, int y)
{
	int i;

	if (key == 125)
		mlx->map[mlx->n].yi += 10;
	else if (key == 126)
		mlx->map[mlx->n].yi -= 10;
	else if (key == 124)
		mlx->map[mlx->n].xi += 10;
	else if (key == 123)
		mlx->map[mlx->n].xi -= 10;
	else
	{
		mlx->map[mlx->n].xi = x - mlx->mouse_x;
		mlx->map[mlx->n].yi = y - mlx->mouse_y;
	}
	ft_draw(mlx);
	return (1);
}

int ft_zoom(int key, t_mlx *mlx)
{
	int i;

	if (key == 69 || key == 4)
		mlx->zoom = (mlx->zoom < 10) ? mlx->zoom + 0.10 : mlx->zoom;
	else
		mlx->zoom = (mlx->zoom > 0.1) ? mlx->zoom - 0.10 : mlx->zoom;
	ft_draw(mlx);
	return (1);
}

int ft_rotz(int key, t_mlx *mlx, double a)
{
	int i;

	if (!a && key == 92)
		mlx->az += 0.10;
	else if (!a)
		mlx->az -= 0.10;
	else
		mlx->az = a;
	ft_draw(mlx);
	return (1);
}

int ft_rotx(int key, t_mlx *mlx, double a)
{
	int i;

	if (!a && key == 91)
		mlx->ax += 0.10;
	else if (!a)
		mlx->ax -= 0.10;
	else
		mlx->ax = a;
	ft_draw(mlx);
	return (1);
}

int ft_roty(int key, t_mlx *mlx, double a)
{
	int i;

	if (!a && key == 88)
		mlx->ay += 0.10;
	else if (!a)
		mlx->ay -= 0.10;
	else
		mlx->ay = a;
	ft_draw(mlx);
	return (1);
}

int ft_keypress(int keycode, void *mlx)
{
	if (keycode == 53)
		ft_close(mlx);
	if (keycode == 124 || keycode == 123 || keycode == 126 || keycode == 125)
		ft_move(keycode, mlx, 0, 0);
	if (keycode == 78 || keycode == 69)
		ft_zoom(keycode, mlx);
	if (keycode == 83 || keycode == 92)
		ft_rotz(keycode, mlx, 0);
	if (keycode == 91 || keycode == 84)
		ft_rotx(keycode, mlx, 0);
	if (keycode == 86 || keycode == 88)
		ft_roty(keycode, mlx, 0);
	return (1);
}
int ft_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	if (button == 4 || button == 5)
		ft_zoom(button, mlx);
	if (button == 1)
	{
		mlx->mouse_b = 1;
		mlx->mouse_x = x - mlx->map[mlx->n].xi;
		mlx->mouse_y = y - mlx->map[mlx->n].yi;
	//	printf("%d", mlx->mouse_b);
	}
return (1);
}

int ft_mouse_release(int button, int x, int y, t_mlx *mlx)
{
		mlx->mouse_b = 0;
	//	printf("%d", mlx->mouse_b);
return (1);
}

int ft_mouse_move(int x, int y, t_mlx *mlx)
{
		if (mlx->mouse_b == 1)
		{
			ft_move(0, mlx, x, y);
		}
return (1);
}
int ft_set_colour(t_point *point)
{
	int red;
	int green;
	int blue;
	if (point->zi == 0)
		return(BASE_COLOUR);
	red = (BASE_COLOUR>>16) + (int)(point->zi * 1.5);
	green = (BASE_COLOUR>>8) & 0xFF + (int)(point->zi * 1.5);
	blue = BASE_COLOUR & 0xFF + (int)(point->zi * 1.5);
	return ((red << 16) | (green << 8) | blue);
}

int ft_map_init(t_mlx *mlx, char ***a)
{
	int i;
	double d;
	if (!(mlx->map = (t_point *)malloc(sizeof(t_point) * (mlx->w * mlx->h + 1))))
		return (0);
	i = -1;
	d = mlx->w > mlx->h ? WIN_WIDTH / mlx->w : WIN_HEIGHT / mlx->h;
	while (++i < mlx->n)
	{
		mlx->map[i].xi = i % mlx->w * d + (d + WIN_WIDTH - d * mlx->w) / 2;
		mlx->map[i].yi = i / mlx->w * d + (d + WIN_HEIGHT - d * mlx->h) / 2;
		mlx->map[i].zi = -d / 7 * ft_atoi((*a)[i]);
		mlx->map[i].ci = (ft_strchr((*a)[i], ',')) ? ft_atoi_base(ft_strchr((*a)[i], 'x') + 1, 16) : ft_set_colour(&mlx->map[i]);
	}
	mlx->map[mlx->n].xi = WIN_WIDTH / 2;
	mlx->map[mlx->n].yi = WIN_HEIGHT / 2;
	ft_win_to_log(mlx);
	cleanarr(a);
	return (1);
}

int main(int argc, char **argv)
{
	int fd;
	char **array;
	int i;
	t_mlx mlx;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putendl("usage: ./fdf mapfile");
		return (0);
	}
	if (!(array = ft_readmap(fd, &mlx.w, &mlx.h, &mlx.n)) || !ft_map_init(&mlx, &array))
	{
		array ? ft_putendl("Unexpected error. Exiting") : array;
		cleanarr(&array);
		return (0);
	}
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, argv[1]);
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
	mlx.ax = 0;
	mlx.ay = 0;
	mlx.az = 0;
	mlx.mouse_b = 0;
	mlx.zoom = 1;
	//ft_rotz(0, &mlx, -0.785);
	//ft_rotx(0, &mlx, 0.785);
	ft_draw(&mlx);
	mlx_hook(mlx.win, 17, 1l << 17, &ft_close, 0);
	mlx_hook(mlx.win, 4, 1L << 2, &ft_mouse_press, &mlx);
	mlx_hook(mlx.win, 5, 1L << 3, &ft_mouse_release, &mlx);
	mlx_hook(mlx.win, 6, 1L << 6, &ft_mouse_move, &mlx);
	mlx_hook(mlx.win, 2, 1L << 6, &ft_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
}