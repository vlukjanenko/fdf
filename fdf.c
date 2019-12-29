/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:27:24 by majosue           #+#    #+#             */
/*   Updated: 2019/12/29 18:12:41 by majosue          ###   ########.fr       */
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
				(*map)[k].x = i * d + (d + WIN_WIDTH - d * w)/2;
				(*map)[k].y = j * d + (d + WIN_HEIGHT - d * h)/2;;
				(*map)[k].z = ft_atoi(a[j * w + i]); 
				(*map)[k].c = 0xFFFFFF;
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
	i = -1;
	mlx.img.data[map[0].y * WIN_WIDTH + map[0].x] = map[0].c;
	while (++i < width * height)
	{
		if (i % width && i > 0)
			ft_draw_line(&mlx,map[i],map[i - 1]);
		if (i / width)
			ft_draw_line(&mlx,map[i],map[i - width]);
	}
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	cleanarr(&array);
}