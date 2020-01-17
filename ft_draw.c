/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:25:58 by majosue           #+#    #+#             */
/*   Updated: 2020/01/17 13:58:44 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_win_to_log(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i <= mlx->n)
	{
		mlx->map[i].xi = mlx->map[i].xi - mlx->map[mlx->n].xi;
		mlx->map[i].yi = mlx->map[i].yi - mlx->map[mlx->n].yi;
	}
}

void	ft_log_to_win(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i < mlx->n)
	{
		mlx->map[i].x = mlx->map[i].xp + WIN_WIDTH / 2;
		mlx->map[i].y = mlx->map[i].yp + WIN_HEIGHT / 2;
	}
}

int		ft_pr1(t_mlx *mlx)
{
	int		i;
	double	k;

	k = 2000;
	i = -1;
	while (++i < mlx->n)
	{
		mlx->map[i].xp = (mlx->p == 'p') ? mlx->map[i].xo /\
		(mlx->map[i].zo / k + 1) : mlx->map[i].xo;
		mlx->map[i].yp = (mlx->p == 'p') ? mlx->map[i].yo /\
		(mlx->map[i].zo / k + 1) : mlx->map[i].yo;
	}
	ft_log_to_win(mlx);
	return (1);
}

int		ft_transform(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i < mlx->n)
	{
		mlx->map[i].xo = mlx->map[i].xi * cos(mlx->ay) * cos(mlx->az) +\
		mlx->map[i].yi * (sin(mlx->ay) * sin(mlx->ax) - cos(mlx->ay) *\
		sin(mlx->az) * cos(mlx->ax)) + mlx->map[i].zi * (cos(mlx->ay) *\
		sin(mlx->az) * sin(mlx->ax) + sin(mlx->ay) * cos(mlx->ax));
		mlx->map[i].yo = mlx->map[i].xi * sin(mlx->az) + mlx->map[i].yi\
		* cos(mlx->az) * cos(mlx->ax) - mlx->map[i].zi * cos(mlx->az) *\
		sin(mlx->ax);
		mlx->map[i].zo = -mlx->map[i].xi * sin(mlx->ay) * cos(mlx->az) +\
		mlx->map[i].yi * (sin(mlx->ay) * sin(mlx->az) * cos(mlx->ax) +\
		cos(mlx->ay) * sin(mlx->ax)) + mlx->map[i].zi * (cos(mlx->ay) *\
		cos(mlx->ax) - sin(mlx->ay) * sin(mlx->az) * sin(mlx->ax));
		mlx->map[i].xo *= mlx->zoom;
		mlx->map[i].yo *= mlx->zoom;
		mlx->map[i].zo *= mlx->zoom;
		mlx->map[i].xo += mlx->map[mlx->n].xi;
		mlx->map[i].yo += mlx->map[mlx->n].yi;
	}
	return (1);
}

int		ft_draw(t_mlx *mlx)
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
	ft_put_help(mlx);
	return (1);
}
