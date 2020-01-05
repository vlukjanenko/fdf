/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 01:19:41 by lmarques          #+#    #+#             */
/*   Updated: 2020/01/03 14:22:40 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h> //for testing

/*
 Defines for the width and height of your window. I suggest you to do the same so
 you can change easily the size of your window later if needed.
*/
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define MARGIN 0
/*
 Here I built a struct of the MLX image :
 It contains everything you need.
 - img_ptr to store the return value of mlx_new_image
 - data to store the return value of mlx_get_data_addr
 - the 3 other variables are pretty much useless, but you'll need
 them in the prototype of mlx_get_data_addr (see the man page for that)
 */
typedef struct	s_img
{
	void		*img_ptr;
	int			*data; //Here you got an int * even though mlx_get_data_addr returns
						//a char *, i'll talk more about this in the .c file.
//Here are the 3 "useless" variables. You can find more informations about these in the man page.
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

/*
 Here is my main struct containing every variables needed by the MLX.
 - mlx_ptr stores the return value of mlx_init
 - win stores the return value of mlx_new_window
 - img will store everything we need for the image part, the struct is described above.
 */
typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
}				t_mlx;

typedef struct s_point
{
	int x;
	int y;
	int z;
	int c;
} t_point;

char **ft_readmap(int fd, int *width, int *height);
int  ft_draw_line(t_mlx *mlx, t_point p1, t_point p2);

#endif