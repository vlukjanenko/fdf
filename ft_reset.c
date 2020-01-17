/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 09:58:21 by majosue           #+#    #+#             */
/*   Updated: 2020/01/17 15:26:44 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_reset(int key, t_mlx *mlx)
{
	if (key == 87)
	{
		mlx->map[mlx->n].yi = WIN_HEIGHT / 4;
		mlx->map[mlx->n].xi = 0;
		mlx->ax = -1.1;
		mlx->ay = -0.68;
		mlx->az = -0.42;
		mlx->zoom = 0.8;
	}
	else
	{
		mlx->map[mlx->n].yi = 0;
		mlx->map[mlx->n].xi = 0;
		mlx->ax = 0;
		mlx->ay = 0;
		mlx->az = 0;
		mlx->zoom = 0.8;
	}
	ft_draw(mlx);
}

int		ft_find_zmax(char **a)
{
	int zmax;
	int z;

	zmax = 0;
	while (*a)
	{
		z = ft_atoi(*a);
		if (z > zmax)
			zmax = z;
		a++;
	}
	return (zmax);
}

int		ft_find_d(t_mlx *mlx, int zmax)
{
	int d;

	d = mlx->w > mlx->h ? WIN_WIDTH / mlx->w : WIN_HEIGHT / mlx->h;
	if (zmax == 0)
		return (d);
	d = (WIN_HEIGHT / zmax < d) ? WIN_HEIGHT / zmax : d;
	return (d);
}

void	ft_put_help(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win, 10, 10, 0xFFFFFF,
"Projection type: \'p\' - perspective \'o\' - parallel");
	mlx_string_put(mlx->mlx_ptr, mlx->win, 10, 30, 0xFFFFFF,\
"Reset to: \'0 on pad\' - view from z \'5 on pad\' - iso view");
	mlx_string_put(mlx->mlx_ptr, mlx->win, 10, 50, 0xFFFFFF,\
"Rotate: \'1,9 on pad\' - z; \'5,6 on pad\' - y;  \'5,6 on pad\' - x");
	mlx_string_put(mlx->mlx_ptr, mlx->win, 10, 70, 0xFFFFFF,\
"Move: arrows and mouse, zoom + - on pad and scroll");
}
