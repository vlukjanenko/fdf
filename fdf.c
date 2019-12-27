/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:27:24 by majosue           #+#    #+#             */
/*   Updated: 2019/12/27 13:25:23 by majosue          ###   ########.fr       */
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
int  line(int **field, int x1, int y1)
{
	int deltax = abs(x1);
	int deltay = abs(y1);
	int error = 0;
	int deltaerr = (deltay + 1);
	int y = 0;
	int x = 0;
	while (x < x1)
	{
		error = error + deltaerr;
		if (error >= (deltax + 1))
		{
			y = y + 1;
			error = error - (deltax + 1);
		}
		(*field)[y * WIN_WIDTH + x] = 0xFFFFFF;
		x++;
	}
	return (0);
 }

int main(int argc, char **argv)
{
	int fd;
	char **array;
	int width;
	int height;
	int i = -1;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putendl("usage: ./fdf mapfile");
		return (0);
	}
			
	if (!(array = ft_readmap(fd, &width, &height)))
		return (0);
	//cleanup(&param, &line);
	printf("Количество элементов %d ", width * height);
	printf("width %d, height %d", width, height);
	while (array[++i])
	{
		printf("%s", array[i]);
	}
	cleanarr(&array);
}