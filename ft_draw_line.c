/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 14:33:29 by majosue           #+#    #+#             */
/*   Updated: 2020/01/14 11:28:37 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}
int get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

int ft_getcolor(t_point p1, t_point end, t_point current)
{
	int red;
	int green;
	int blue;
	double percentage;
	t_point start;

	start = p1;
	start.x = p1.xp + WIN_WIDTH / 2;
	start.y = p1.yp + WIN_HEIGHT / 2;

	percentage = (end.x - start.x > end.y - start.y) ? percent(start.x, end.x, current.x) : percent(start.y, end.y, current.y);
	red = get_light((start.ci >> 16) & 0xFF, (end.ci >> 16) & 0xFF, percentage);
    green = get_light((start.ci >> 8) & 0xFF, (end.ci >> 8) & 0xFF, percentage);
    blue = get_light(start.ci & 0xFF, end.ci & 0xFF, percentage);
    return ((red << 16) | (green << 8) | blue);
}

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
		if (p1.y < WIN_HEIGHT && p1.y >= 0 && p1.x < WIN_WIDTH && p1.x > 0)
			(*mlx).img.data[p1.y * WIN_WIDTH + p1.x] = ft_getcolor(p1, p2, p1);
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
	if (p1.y < WIN_HEIGHT && p1.y >= 0 && p1.x < WIN_WIDTH && p1.x > 0)
		(*mlx).img.data[p1.y * WIN_WIDTH + p1.x] = ft_getcolor(p1, p2, p1);
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
