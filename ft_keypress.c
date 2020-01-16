/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:43:06 by majosue           #+#    #+#             */
/*   Updated: 2020/01/16 16:55:18 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_keypress(int keycode, void *mlx)
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

int	ft_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	if (button == 4 || button == 5)
		ft_zoom(button, mlx);
	if (button == 1 && y > 0)
	{
		mlx->mouse_b = 1;
		mlx->mouse_x = x - mlx->map[mlx->n].xi;
		mlx->mouse_y = y - mlx->map[mlx->n].yi;
	}
	return (1);
}

int	ft_mouse_release(int button, int x, int y, t_mlx *mlx)
{
	mlx->mouse_b = 0;
	return (1);
}

int	ft_mouse_move(int x, int y, t_mlx *mlx)
{
	if (mlx->mouse_b == 1)
		ft_move(0, mlx, x, y);
	return (1);
}
void ft_events(t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 1l << 17, ft_close, mlx);
	mlx_hook(mlx->win, 4, 1L << 2, ft_mouse_press, mlx);
	mlx_hook(mlx->win, 5, 1L << 3, ft_mouse_release, mlx);
	mlx_hook(mlx->win, 6, 1L << 6, ft_mouse_move, mlx);
	mlx_hook(mlx->win, 2, 1L << 6, ft_keypress, mlx);
	mlx_loop(mlx->mlx_ptr);
}