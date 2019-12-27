/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:27:24 by majosue           #+#    #+#             */
/*   Updated: 2019/12/19 21:22:14 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	t_mlx	mlx; //Here I first create my struct that will contains all the "MLX stuff"
	int		count_w;
	int		count_h;

	count_h = -1;
	//First you need to call mlx_init and store its return value.
	mlx.mlx_ptr = mlx_init();
	//Now do the same with mlx_new_window
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example");
	//One more time with mlx_new_image
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	/*
	 Now the important part :
	 mlx_get_data_addr will return a char* that is 4 times the (width * height) of your image.
	 Why so ? Let me explain : This char* will represent your image, pixel by pixel,
	 and the values of this array are the colors. That's why the array is 4 times bigger :
	 you need 4 char to code the color of each pixels (one for Red, Green and Blue) and one for the alpha.
	 But... it's not very convenient, right ? So here is my little trick : you cast
	 mlx_get_data_addr as an int* and store it in an int*.
	 This way, the array will have the exact same size as your window, and each indexук
	 will represent one complete color of a pixel !
	*/
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l,
		&mlx.img.endian);
	/*
	 Now just a little example : here is a loop that will draw each pixels that
	 have an odd width in white and the ones that have an even width in black.
	*/
	while (++count_h < WIN_HEIGHT)
	{
		count_w = -1;
		while (++count_w < WIN_WIDTH)
		{
			if (count_w % 2)
				/*
				 As you can see here instead of using the mlx_put_pixel function
				 I just assign a color to each pixel one by one in the image,
				 and the image will be printed in one time at the end of the loop.
				 Now one thing to understand here is that you're working on a 1-dimensional
				 array, while your window is (obviously) 2-dimensional.
				 So, instead of having data[height][width] here you'll have the following
				 formula : [current height * max width + current width] (as you can see below)
				*/
				mlx.img.data[count_h * WIN_WIDTH + count_w] = 0xFFFFFF;
			else
				mlx.img.data[count_h * WIN_WIDTH + count_w] = 0;
		}
	}
	//Now you just have to print the image using mlx_put_image_to_window !
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
© 2019 GitHub, Inc.
Terms
Privacy
Security
Status
Help
Contact GitHub
Pricing
API
Training
Blog
About




























/* typedef struct s_mlx
{
    void *m;
    void *w;
    int x;
    int y;
    int col;
} t_mlx;



void ft_putchar(char c)
{
    write(1, &c, 1);
}

int deal_mouse(int button, int x, int y, void *param)
{
   printf("%d\n", button);
   if (button)
   {
    mlx_pixel_put((*(t_mlx*)param).m, (*(t_mlx*)param).w, x, y, 0xFFFFFF);
   // mlx_mouse_hook ((*(t_mlx*)param).w, deal_mouse, param);
   }
    //printf("%d\n", key);
    
   // ft_putchar('X');
   // *(int*)param = *(int*)param + 1;
   // printf("%d\n", *(int*)param);
    return (0); 
}
int deal_key(int key, void *param)
{
if (key == 125)
    (*(t_mlx*)param).y = (*(t_mlx*)param).y + 1;
else if (key == 124)
    (*(t_mlx*)param).x = (*(t_mlx*)param).x + 1;
else if (key == 123)
    (*(t_mlx*)param).x = (*(t_mlx*)param).x - 1;
else if (key == 126)
    (*(t_mlx*)param).y = (*(t_mlx*)param).y - 1;


mlx_pixel_put((*(t_mlx*)param).m, (*(t_mlx*)param).w, (*(t_mlx*)param).x, (*(t_mlx*)param).y, 0xFFFFFF);  
    //printf("%d\n", key);
    
   // ft_putchar('X');
   // *(int*)param = *(int*)param + 1;
   // printf("%d\n", *(int*)param);
    return (0);
}

int main()
{
    int y;
    y = 10;
    t_mlx q;

    void *mlx_ptr;
    void *win_ptr;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
    mlx_pixel_put(mlx_ptr, win_ptr, 10, 10, 0xFFFFFF);
    q.m = mlx_ptr;
    q.w = win_ptr;
    q.x = 11;
    q.y = 11;
    mlx_string_put (mlx_ptr, win_ptr, 11, y, 0xFFFFFF, "Draw character string");
    mlx_key_hook(win_ptr, deal_key, &q);
   // mlx_mouse_hook (win_ptr, deal_mouse, &q);
    mlx_hook (win_ptr, 6, 4, deal_mouse, &q);
    mlx_loop(mlx_ptr);

} */