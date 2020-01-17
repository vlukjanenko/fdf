/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:27:24 by majosue           #+#    #+#             */
/*   Updated: 2020/01/17 13:40:08 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft.h"

void	cleanarr(char ***array)
{
	char **tmp;

	if (*array)
	{
		tmp = *array;
		while (**array)
		{
			free(**array);
			(*array)++;
		}
		free(tmp);
	}
}

int		ft_close(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	free(mlx->map);
	exit(0);
	return (0);
}

int		ft_map_init(t_mlx *mlx, char ***a)
{
	int		i;
	double	d;
	int		zmax;

	if (!(mlx->map = (t_point *)malloc(sizeof(t_point) *\
	(mlx->w * mlx->h + 1))))
		return (0);
	zmax = ft_find_zmax(*a);
	i = -1;
	d = ft_find_d(mlx, zmax);
	while (++i < mlx->n)
	{
		mlx->map[i].xi = i % mlx->w * d + (d + WIN_WIDTH - d * mlx->w) / 2;
		mlx->map[i].yi = i / mlx->w * d + (d + WIN_HEIGHT - d * mlx->h) / 2;
		mlx->map[i].zi = -d * ft_atoi((*a)[i]);
		mlx->map[i].ci = (ft_strchr((*a)[i], ',')) ? ft_atoi_base(ft_strchr(\
		(*a)[i], 'x') + 1, 16) : ft_set_colour(&mlx->map[i], zmax);
	}
	mlx->p = 'o';
	mlx->map[mlx->n].xi = WIN_WIDTH / 2;
	mlx->map[mlx->n].yi = WIN_HEIGHT / 2;
	ft_win_to_log(mlx);
	cleanarr(a);
	return (1);
}

int		ft_mlx_init(t_mlx *mlx, char *name)
{
	if (!(mlx->mlx_ptr = mlx_init()) ||\
!(mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, name)) ||\
!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT)))
		return (0);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,\
	&mlx->img.size_l, &mlx->img.endian);
	mlx->ax = 0;
	mlx->ay = 0;
	mlx->az = 0;
	mlx->mouse_b = 0;
	ft_reset(87, mlx);
	ft_draw(mlx);
	return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	**array;
	t_mlx	mlx;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putendl("usage: ./fdf mapfile");
		return (0);
	}
	if (!(array = ft_readmap(fd, &mlx.w, &mlx.h, &mlx.n)) ||\
	!ft_map_init(&mlx, &array))
	{
		array ? ft_putendl("Unexpected error. Exiting") : array;
		cleanarr(&array);
		return (0);
	}
	if (!ft_mlx_init(&mlx, argv[1]))
	{
		ft_putendl("usage: ./fdf mapfile");
		return (0);
	}
	ft_events(&mlx);
	return (0);
}
