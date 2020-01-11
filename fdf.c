/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:27:24 by majosue           #+#    #+#             */
/*   Updated: 2020/01/10 20:53:38 by majosue          ###   ########.fr       */
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

int ft_close(void *param)
{
    (void)param;
    exit(0);
}

int ft_log_to_win(t_mlx *mlx) //сюда присылаем то что связываем на экране? за границы в границы? Неее границы в отрисовке линий уже
{
	int i;
	int n;
	
	n = (*mlx).map[0].w * (*mlx).map[0].h;
	i = -1;
	while (++i < n)
	{
		(*mlx).map[i].x = (1.0 / 2) * ((*mlx).map[i].xp + 1) * WIN_WIDTH;
		(*mlx).map[i].y = (-1.0 / 2) * ((*mlx).map[i].yp - 1) * WIN_HEIGHT;
	}
	return (1);
}
int ft_pr1(t_mlx *mlx)
{
	int n;
	int m;
	int i;
	double k;

	k = 10;
	n = (*mlx).map[0].w * (*mlx).map[0].h;
	i = -1;
	while (++i < n)
	{
		(*mlx).map[i].xp = (*mlx).map[i].xo /((*mlx).map[i].zo / k + 1);
		(*mlx).map[i].yp = (*mlx).map[i].yo /((*mlx).map[i].zo / k + 1);
		/* (*mlx).map[i].xp = (*mlx).map[i].xo;
		(*mlx).map[i].yp = (*mlx).map[i].yo; */
	}
	ft_log_to_win(mlx);
	return (1);
}
int ft_draw(t_mlx *mlx)
{
	int n;
	int m;
	int i;

	n = (*mlx).map[0].w * (*mlx).map[0].h;
	i = -1;
	mlx_clear_window((*mlx).mlx_ptr, (*mlx).win);
	m = WIN_WIDTH * WIN_HEIGHT;
	while (++i < m)
		(*mlx).img.data[i] = 0;	
	ft_pr1(mlx);
	i = -1;
	while (++i < n)
	{
		if (i % (*mlx).map[0].w && i > 0)
			ft_draw_line(mlx,(*mlx).map[i],(*mlx).map[i - 1]);
		if (i / (*mlx).map[0].w)
			ft_draw_line(mlx,(*mlx).map[i],(*mlx).map[i - (*mlx).map[0].w]);
	}
	mlx_put_image_to_window((*mlx).mlx_ptr, (*mlx).win, (*mlx).img.img_ptr, 0, 0);
	return (1);
}

int ft_move_r(t_mlx *mlx)
{
	int n;
	int i;

	i = -1;
	n = (*mlx).map[0].w * (*mlx).map[0].h;
	while (++i < n)
	{ 
		(*mlx).map[i].xo += 0.01;
	}
	ft_draw(mlx);
	return (1);
}

int ft_move_l(t_mlx *mlx)
{
	int n;
	int i;

	i = -1;
	n = (*mlx).map[0].w * (*mlx).map[0].h;
	while (++i < n)
	{ 
		(*mlx).map[i].xo -= 0.01;
	}
	ft_draw(mlx);
	return (1);
}

int ft_move_u(t_mlx *mlx)
{
	int n;
	int i;

	i = -1;
	n = (*mlx).map[0].w * (*mlx).map[0].h;
	while (++i < n)
	{ 
		(*mlx).map[i].yo += 0.01;
	}
	ft_draw(mlx);
	return (1);
}

int ft_move_d(t_mlx *mlx)
{
	int n;
	int i;

	i = -1;
	n = (*mlx).map[0].w * (*mlx).map[0].h;
	while (++i < n)
	{ 
		(*mlx).map[i].yo -= 0.01;
	}
	ft_draw(mlx);
	return (1);
}

int ft_zoom(int key, t_mlx *mlx)
{
	int n;
	int i;

	i = -1;
	n = (*mlx).map[0].w * (*mlx).map[0].h;
		
	while (++i < n)
	{ 
		(*mlx).map[i].xo = key == 78 ? (*mlx).map[i].xo / 1.1 :  (*mlx).map[i].xo * 1.1;
		(*mlx).map[i].yo = key == 78 ? (*mlx).map[i].yo / 1.1 :  (*mlx).map[i].yo * 1.1;		
	}
	ft_draw(mlx);
	return (1);
}

int ft_rot(int key, t_mlx *mlx, double a)
{
	int n;
	int i;
	//double a;

	if (!a)
		a = key == 15 ? 0.07 : -0.07;
	i = -1;
	n = (*mlx).map[0].w * (*mlx).map[0].h;

	while (++i < n)
	{ 
		(*mlx).map[i].xo = (*mlx).map[i].xo * cos(a) - (*mlx).map[i].yo * sin(a);
		(*mlx).map[i].yo = (*mlx).map[i].xo * sin(a) + (*mlx).map[i].yo * cos(a);
	}
	ft_draw(mlx);
	return (1);
}

int ft_rotx(int key, t_mlx *mlx, double a)
{
	int n;
	int i;
	//double a;

	if (!a)
		a = key == 14 ? 0.07 : -0.07;
	i = -1;
	n = (*mlx).map[0].w * (*mlx).map[0].h;

	while (++i < n)
	{ 
		//(*mlx).map[i].xo = (*mlx).map[i].xo * cos(a) - (*mlx).map[i].yo * sin(a);
		(*mlx).map[i].yo = (*mlx).map[i].yo * cos(a) + (*mlx).map[i].zo * sin(a);
		(*mlx).map[i].zo = -(*mlx).map[i].yo * sin(a) + (*mlx).map[i].zo * cos(a);
	}
	ft_draw(mlx);
	return (1);
}

int ft_roty(int key, t_mlx *mlx, double a)
{
	int n;
	int i;
	//double a;
	if (!a)
		a = key == 12 ? 0.07 : -0.07;
	i = -1;
	n = (*mlx).map[0].w * (*mlx).map[0].h;

	while (++i < n)
	{ 
		(*mlx).map[i].xo = (*mlx).map[i].xo * cos(a) - (*mlx).map[i].zo * sin(a);
	//	(*mlx).map[i].yo = (*mlx).map[i].yo * cos(a) + (*mlx).map[i].zo * sin(a);
		(*mlx).map[i].zo = (*mlx).map[i].xo * sin(a) + (*mlx).map[i].zo * cos(a);
	}
	ft_draw(mlx);
	return (1);
}

int ft_keypress(int keycode, void *mlx)
{
	if(keycode == 53)
		ft_close(0);
	if(keycode == 124)
		ft_move_r(mlx);
	if(keycode == 123)
		ft_move_l(mlx);
	if(keycode == 126)
		ft_move_u(mlx);	
	if(keycode == 125)
		ft_move_d(mlx);		
	if(keycode == 78 || keycode == 69)
		ft_zoom(keycode, mlx);
	if(keycode == 15 || keycode == 17)
		ft_rot(keycode, mlx, 0);		
	if(keycode == 14 || keycode == 2)
		ft_rotx(keycode, mlx, 0);		
	if(keycode == 12 || keycode == 13)
		ft_roty(keycode, mlx, 0);		
	return (1);
}

int ft_map_pos(t_point **map)
{
	int i;
	int n;
	double dx;
	double dy;

	n = (*map)[0].w * (*map)[0].h;
		dx = ((*map)[(*map)[0].w - 1].xo - (*map)[0].xo) / 2;
		dy = ((*map)[n - 1].yo - (*map)[0].yo) / 2;
	i = -1;
	while (++i < n)
	{
		(*map)[i].xo -= dx;
		(*map)[i].yo -= dy;
	}
return (1);
}
int ft_map_init(t_point **map, char **a, int w, int h)
{
	int i;
	int j;
	int k;
	double d;
	
	k = 0;
	(*map) = (t_point*)malloc(sizeof(t_point) * w * h);
	i = -1;
	j = -1;
	d = w > h ? 1.0 / w : 1.0 / h;

	while (++j < h)
		{
			while(++i < w)
			{
				(*map)[k].xo = i * d;
				// - (d * (w / 2 - w % 2));
				(*map)[k].yo = -j * d * WIN_WIDTH / WIN_HEIGHT;
				// + (d * h / 2.0);
				(*map)[k].zo = -d * ft_atoi(a[j * w + i]); 
				(*map)[k].c = 0xFFFFFF;
				(*map)[k].w = w;
				(*map)[k].h = h;
				k++;
			}
		i = -1;
		}
return (1);
}

int main(int argc, char **argv)
{
	int fd;
	char **array;
	int width;
	int height;
	int i;
	t_point *map;	
	t_mlx	mlx;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putendl("usage: ./fdf mapfile");
		return (0);
	}
	if (!(array = ft_readmap(fd, &width, &height)))
		return (0);
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, argv[1]);
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
	ft_map_init(&map, array, width, height);
	ft_map_pos(&map);
	mlx.map = map;
	ft_rot(0, &mlx, 0.7);
	ft_rotx(0, &mlx, -0.14);
	//ft_roty(0, &mlx, -0.3);
	ft_draw(&mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.win, 17, 1l<<17, &ft_close, 0);
	mlx_hook(mlx.win, 2, 1l<<17, &ft_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
	cleanarr(&array);
}