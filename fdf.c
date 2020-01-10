/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:27:24 by majosue           #+#    #+#             */
/*   Updated: 2020/01/10 09:20:26 by majosue          ###   ########.fr       */
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

int ft_pr1(t_mlx *mlx)
{
	int n;
	int m;
	int i;
	int k;
	int dx;
	int dy;
	dx = WIN_WIDTH / 2;
	dy = WIN_HEIGHT / 2;

	k = 50;
	n = (*mlx).map[0].w * (*mlx).map[0].h;
	i = -1;
	while (++i < n)
	{
		(*mlx).map[i].xo -= dx;
		(*mlx).map[i].yo -= dy;
		/* (*mlx).map[i].x = (*mlx).map[i].xo /((*mlx).map[i].zo / k + 1) + dx;
		(*mlx).map[i].y = (*mlx).map[i].yo /((*mlx).map[i].zo / k + 1) + dy; */
		(*mlx).map[i].x = (*mlx).map[i].xo + dx;
		(*mlx).map[i].y = (*mlx).map[i].yo + dy;
	}
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
		(*mlx).map[i].xo += 5;
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
		(*mlx).map[i].xo -= 5;
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
		(*mlx).map[i].yo -= 5;
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
		(*mlx).map[i].yo += 5;
	}
	ft_draw(mlx);
	return (1);
}

int ft_zoom(int key, t_mlx *mlx)
{
	int n;
	int i;
	int dx;
	int dy;
	
	i = -1;
	n = (*mlx).map[0].w * (*mlx).map[0].h;
	dx = WIN_WIDTH / 2;
	dy = WIN_HEIGHT / 2;	
	while (++i < n)
	{
		(*mlx).map[i].xo -= dx;
		(*mlx).map[i].yo -= dy;
	}
	i = -1;
	while (++i < n)
	{ 
		(*mlx).map[i].xo = key == 78 ? (*mlx).map[i].xo / 1.5 :  (*mlx).map[i].xo * 1.5; //тут нужно ограничить минимум
		(*mlx).map[i].yo = key == 78 ? (*mlx).map[i].yo / 1.5 :  (*mlx).map[i].yo * 1.5;		
	}
	i = -1;
	while (++i < n)
	{
		(*mlx).map[i].xo += dx;
		(*mlx).map[i].yo += dy;
	}
	ft_draw(mlx);
	return (1);
}

int ft_rot(t_mlx *mlx)
{
	int n;
	int i;
	int dx;
	int dy;

	i = -1;
	n = (*mlx).map[0].w * (*mlx).map[0].h;
	dx = WIN_WIDTH / 2;
	dy = WIN_HEIGHT / 2;	

	while (++i < n)
	{
		(*mlx).map[i].xo -= dx;
		(*mlx).map[i].yo -= dy;
	}
	i = -1;
	while (++i < n)
	{ 
		(*mlx).map[i].xo = (*mlx).map[i].xo * cos(0.01) - (*mlx).map[i].yo * sin(0.01);
		(*mlx).map[i].yo = (*mlx).map[i].xo * sin(0.01) + (*mlx).map[i].yo * cos(0.01);
	}
	i = -1;
	while (++i < n)
	{
		(*mlx).map[i].xo += dx;
		(*mlx).map[i].yo += dy;
	}
	i = -1;	
	ft_draw(mlx);
	return (1);
}

int ft_keypress(int keycode, void *mlx)
{
	//(void)map;
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
	if(keycode == 15)
		ft_rot(mlx);		
	return (1);
}

int ft_map_init(t_point **map, char **a, int w, int h)
{
	int i;
	int j;
	int k;
	int d;
	
	k = 0;
	(*map) = (t_point*)malloc(sizeof(t_point) * w * h);
	i = -1;
	j = -1;
	d = w > h ? WIN_WIDTH / w - 3 : WIN_HEIGHT / h - 3;
	while (++j < h)
		{
			while(++i < w)
			{
				(*map)[k].xo = i * d + (d + WIN_WIDTH - d * w)/2;
				(*map)[k].yo = j * d + (d + WIN_HEIGHT - d * h)/2;
				(*map)[k].zo = -ft_atoi(a[j * w + i]); 
				(*map)[k].x = i * d + (d + WIN_WIDTH - d * w)/2;
				(*map)[k].y = j * d + (d + WIN_HEIGHT - d * h)/2;
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
	mlx.map = map;
	i = -1;
	mlx.img.data[(int)(map[0].y * WIN_WIDTH + map[0].x)] = map[0].c;
	/* while (++i < width * height)
	{
		if (i % width && i > 0)
			ft_draw_line(&mlx,map[i],map[i - 1]);
		if (i / width)
			ft_draw_line(&mlx,map[i],map[i - width]);
	} */
	ft_draw(&mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.win, 17, 1l<<17, &ft_close, 0);
	mlx_hook(mlx.win, 2, 1l<<17, &ft_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
	cleanarr(&array);
}