/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 01:19:41 by lmarques          #+#    #+#             */
/*   Updated: 2020/01/17 14:50:11 by majosue          ###   ########.fr       */
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
# define FLAT_COLOUR 0xff9900
# define HIGH_COLOUR 0x008F11

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
int				ft_set_colour(t_point *point, int zmax);
int				ft_getcolor(t_point p1, t_point end, t_point current);
void			ft_reset(int key, t_mlx *mlx);
int				ft_find_zmax(char **a);
int				ft_find_d(t_mlx *mlx, int zmax);
void			ft_put_help(t_mlx *mlx);

#endif
