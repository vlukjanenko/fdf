/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 14:33:29 by majosue           #+#    #+#             */
/*   Updated: 2020/01/08 12:26:49 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_swap(t_point *p1, t_point *p2)
{
	t_point tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	ft_xstep(t_mlx *mlx, t_point p1, t_point p2)
{
	int deltax;
	int deltay;
	int error;
	int deltaerr;
	int diry;

	deltax = abs(p2.x - p1.x);
	deltay = abs(p2.y - p1.y);
	error = 0;
	deltaerr = (deltay + 1);
	diry = (p2.y - p1.y) < 0 ? -1 : 1;
	while (p1.x <= p2.x)
	{
		(*mlx).img.data[p1.y * WIN_WIDTH + p1.x] = 0xFFFFFF;
		error = error + deltaerr;
		if (error >= (deltax + 1))
		{
			p1.y = p1.y + diry;
			error = error - (deltax + 1);
		}
		p1.x++;
	}
}

void	ft_ystep(t_mlx *mlx, t_point p1, t_point p2)
{
	int deltax;
	int deltay;
	int error;
	int deltaerr;
	int dirx;

	deltax = abs(p2.x - p1.x);
	deltay = abs(p2.y - p1.y);
	deltaerr = (deltax + 1);
	error = 0;
	dirx = (p2.x - p1.x) < 0 ? -1 : 1;
	while (p1.y <= p2.y)
	{
		(*mlx).img.data[p1.y * WIN_WIDTH + p1.x] = 0xFFFFFF;
		error = error + deltaerr;
		if (error >= (deltay + 1))
		{
			p1.x = p1.x + dirx;
			error = error - (deltay + 1);
		}
		p1.y++;
	}
}

int		ft_draw_line(t_mlx *mlx, t_point p1, t_point p2)
{
	if (abs(p2.x - p1.x) >= abs(p2.y - p1.y))
	{
		p2.x < p1.x ? ft_swap(&p2, &p1) : p2.x;
		ft_xstep(mlx, p1, p2);
	}
	else
	{
		p2.y < p1.y ? ft_swap(&p2, &p1) : p2.y;
		ft_ystep(mlx, p1, p2);
	}
	return (1);
}
