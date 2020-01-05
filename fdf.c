/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:27:24 by majosue           #+#    #+#             */
/*   Updated: 2020/01/04 19:18:27 by majosue          ###   ########.fr       */
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
	d = w > h ? WIN_WIDTH / w - 1 : WIN_HEIGHT / h - 1;
	while (++j < h)
		{
			while(++i < w)
			{
				(*map)[k].x = i * d + (d + WIN_WIDTH - d * w)/2;
				(*map)[k].y = j * d + (d + WIN_HEIGHT - d * h)/2;;
				(*map)[k].z = ft_atoi(a[j * w + i]);
				(*map)[k].c = 0xFFFFFF - ft_atoi(a[j * w + i]);
				k++;
			}
		i = -1;
		}
return (1);
}


int deal_key(int key, void *mlx)
{
int i;

i = -1;
if (key == 65307)
	exit(0);
printf("%d\n", key);
if (key == 65363)
	{
		while (++i < WIN_HEIGHT * WIN_WIDTH)
		(*(t_mlx*)mlx).img.data[i] = 0;
		mlx_put_image_to_window((*(t_mlx*)mlx).mlx_ptr, (*(t_mlx*)mlx).win,(*(t_mlx*)mlx).img.img_ptr, 0, 0);
	}
printf("%d\n", key);
    
   // ft_putchar('X');
   // *(int*)param = *(int*)param + 1;
   // printf("%d\n", *(int*)param);
    return (0);
}
int deal_mouse(int button,int x,int y,void *param)
{
printf("B = %d\n", button);
 printf("x = %d\n", x);
 printf("y = %d\n", y);   
   // ft_putchar('X');
   // *(int*)param = *(int*)param + 1;
   // printf("%d\n", *(int*)param);
    return (0);
}

int close_w(void *param)
{
    (void)param;
    exit(0);
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
	mlx_key_hook(mlx.win, &deal_key, &mlx);
	mlx_mouse_hook(mlx.win, &deal_mouse, 0);
	mlx_hook(mlx.win, 17, (1L<<17), &close_w, 0);
	mlx_loop(mlx.mlx_ptr);
	while (*array)
		printf("%s ", *array++);
	cleanarr(&array);
}