/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 01:19:41 by lmarques          #+#    #+#             */
/*   Updated: 2020/01/16 17:36:53 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>

# define WIN_WIDTH 1600
# define WIN_HEIGHT 1200
# define BASE_COLOUR 0xff9900

typedef struct	s_img
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_point
{
	int		x;
	double	xo;
	double	xp;
	double	xi;
	int		y;
	double	yo;
	double	yp;
	double	yi;
	double	zo;
	double	zi;
	int		c;
	int		ci;
}				t_point;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_point		*map;
	int			w;
	int			h;
	int			n;
	double		zoom;
	float		ax;
	float		ay;
	float		az;
	int			mouse_b;
	int			mouse_x;
	int			mouse_y;
	int			p;
	t_img		img;
}				t_mlx;

char			**ft_readmap(int fd, int *width, int *height, int *number);
int				ft_draw_line(t_mlx *mlx, t_point p1, t_point p2);
int				ft_atoi_base(const char *nbr, unsigned int base);
int				ft_move(int key, t_mlx *mlx, int x, int y);
int				ft_zoom(int key, t_mlx *mlx);
int				ft_rotz(int key, t_mlx *mlx, double a);
int				ft_rotx(int key, t_mlx *mlx, double a);
int				ft_roty(int key, t_mlx *mlx, double a);
int				ft_draw(t_mlx *mlx);
void			ft_events(t_mlx *mlx);
int				ft_close(t_mlx *mlx);
void			ft_win_to_log(t_mlx *mlx);
int				ft_set_colour(t_point *point);
int				ft_getcolor(t_point p1, t_point end, t_point current);

#endif
