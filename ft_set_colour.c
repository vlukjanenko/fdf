/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_colour.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:02:30 by majosue           #+#    #+#             */
/*   Updated: 2020/01/16 17:08:07 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		ft_getcolor(t_point p1, t_point end, t_point current)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;
	t_point	start;

	start = p1;
	start.x = p1.xp + WIN_WIDTH / 2;
	start.y = p1.yp + WIN_HEIGHT / 2;
	percentage = (end.x - start.x > end.y - start.y) ? percent(start.x, end.x,\
	current.x) : percent(start.y, end.y, current.y);
	red = get_light((start.ci >> 16) & 0xFF, (end.ci >> 16) & 0xFF, percentage);
	green = get_light((start.ci >> 8) & 0xFF, (end.ci >> 8) & 0xFF, percentage);
	blue = get_light(start.ci & 0xFF, end.ci & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

int		ft_set_colour(t_point *point)
{
	int red;
	int green;
	int blue;

	if (point->zi == 0)
		return (BASE_COLOUR);
	red = (BASE_COLOUR >> 16) + (int)(point->zi * 1.5);
	green = (BASE_COLOUR >> 8) & 0xFF + (int)(point->zi * 1.5);
	blue = BASE_COLOUR & 0xFF + (int)(point->zi * 1.5);
	return ((red << 16) | (green << 8) | blue);
}
