/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:27:24 by majosue           #+#    #+#             */
/*   Updated: 2019/12/28 19:10:20 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

typedef struct s_point
{
	float x;
	float y;
	float z;
	int c;
} t_point;

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
int  line(int **field, int x1, int y1)
{
	int deltax = abs(x1);
	int deltay = abs(y1);
	int error = 0;
	int deltaerr = (deltay + 1);
	int y = 0;
	int x = 0;
	while (x < x1)
	{
		error = error + deltaerr;
		if (error >= (deltax + 1))
		{
			y = y + 1;
			error = error - (deltax + 1);
		}
		(*field)[y * WIN_WIDTH + x] = 0xFFFFFF;
		x++;
	}
	return (0);
 }
 void ft_c2(float *x, float *y, int xw, int yw)
 {
	 *x = (xw - MARGIN)/(1.0 / 2) * (WIN_WIDTH - 2 * MARGIN) - 1;
	 *y = (yw - MARGIN)/(-1.0 / 2) * (WIN_HEIGHT - 2 * MARGIN) + 1;
 }

 int ft_c(float x, float y, int w, int h)
{
	int xw;
	int yw;

	xw = MARGIN + (1.0 / 2) * (x + 1) * (w - 2 * MARGIN);
	yw = MARGIN + (-1.0 / 2) * (y - 1) * (h - 2 * MARGIN);
	// xw = w / 2 + x;
	// yw = h / 2 + y;
	//printf("x = %d, y = %d", xw, yw);
	return (yw * w + xw);
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
	d = w >= h ? WIN_WIDTH / w - 1 : WIN_HEIGHT / h - 1;
	while (++j < h)
		{
			while(++i < w)
			{
				(*map)[k].x = (i * d + (WIN_WIDTH - w * d) / 2 - MARGIN)/((1.0 / 2) * (WIN_WIDTH - 2 * MARGIN)) - 1;
				(*map)[k].y = (j * d + (WIN_HEIGHT - h * d) / 2  - MARGIN)/((-1.0 / 2) * (WIN_HEIGHT - 2 * MARGIN)) + 1;
				(*map)[k].z = ft_atoi(a[j * w + i]); 
				(*map)[k].c = 0xFFFFFF;
				//printf("x = %f, y = %f, z = %f\n", (*map)[k].x, (*map)[k].y, (*map)[k].z);
				k++;
				//пересчитывается координата ставится в мликс
				//(*mlx).img.data[ft_c(i * d,j * d, WIN_WIDTH, WIN_HEIGHT)] = 0xFFFFFF - ft_atoi(a[ft_c(i, j, w, h)]);
			}
		i = -1;
		}
return (1);
}

/* int ft_map_init(t_point **map, char **a, int w, int h)
{
	int i;
	int j;
	int k;
	int d;

	k = 0;
	(*map) = (t_point*)malloc(sizeof(t_point) * w * h);
	i = -1 - w / 2;
	j = -1 - h / 2;
	d = WIN_WIDTH / w - 1;
	while (++j < h / 2)
		{
			while(++i < w / 2)
			{
				(*map)[k].x = i;
				(*map)[k].y = j;
				(*map)[k].z = ft_atoi(a[ft_c(i, j, w, h)]); 
				(*map)[k].c = 0xFFFFFF;
				printf("x = %d, y = %d, c = %d\n", (*map)[k].x, (*map)[k].y, (*map)[k].c);
				k++;
				//пересчитывается координата ставится в мликс
				//(*mlx).img.data[ft_c(i * d,j * d, WIN_WIDTH, WIN_HEIGHT)] = 0xFFFFFF - ft_atoi(a[ft_c(i, j, w, h)]);
			}
		i = -1 - w / 2;
		}
return (1);
} */


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
	printf("| %d  %d |", width, height);
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, argv[1]);
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
	
	ft_map_init(&map, array, width, height);
	//draw(&mlx,0,0);
	i = -1;
	while (++i < width * height)
	{
		//printf("x = %d, y = %d, z = %d\n", map[i].x, map[i].y, map[i].z);
		mlx.img.data[ft_c(map[i].x, map[i].y, WIN_WIDTH, WIN_HEIGHT)] = map[i].c;
	}
	 mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	 mlx_loop(mlx.mlx_ptr);
	
	
	cleanarr(&array);
}