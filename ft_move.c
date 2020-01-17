/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:14:38 by majosue           #+#    #+#             */
/*   Updated: 2020/01/17 15:27:15 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_move(int key, t_mlx *mlx, int x, int y)
{
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

int	ft_zoom(int key, t_mlx *mlx)
{
	if (key == 69 || key == 4)
		mlx->zoom = (mlx->zoom < 1.5) ? mlx->zoom + 0.10 : mlx->zoom;
	else
		mlx->zoom = (mlx->zoom > 0.5) ? mlx->zoom - 0.10 : mlx->zoom;
	ft_draw(mlx);
	return (1);
}

int	ft_rotz(int key, t_mlx *mlx, double a)
{
	if (!a && key == 92)
		mlx->az += 0.10;
	else if (!a)
		mlx->az -= 0.10;
	else
		mlx->az = a;
	ft_draw(mlx);
	return (1);
}

int	ft_rotx(int key, t_mlx *mlx, double a)
{
	if (!a && key == 84)
		mlx->ax += 0.10;
	else if (!a)
		mlx->ax -= 0.10;
	else
		mlx->ax = a;
	ft_draw(mlx);
	return (1);
}

int	ft_roty(int key, t_mlx *mlx, double a)
{
	if (!a && key == 86)
		mlx->ay += 0.10;
	else if (!a)
		mlx->ay -= 0.10;
	else
		mlx->ay = a;
	ft_draw(mlx);
	return (1);
}
