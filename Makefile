# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majosue <majosue@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 10:14:46 by majosue           #+#    #+#              #
#    Updated: 2020/01/03 14:36:11 by majosue          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  fdf
HEADER = fdf.h
INCLUDES = -I libft/ -I minilibx/
MINILIBX = minilibx/libmlx.a
LIBFT = libft/libft.a
COMPILERC = gcc
FLAGS = -g #-Wall -Wextra -Werror
SOURCES  =  fdf.c ft_readmap.c ft_draw_line.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)  $(LIBFT)
	#$(COMPILERC) -o $(NAME) $(OBJECTS) $(INCLUDES) -L minilibx_macos/ -lmlx -framework OpenGL -framework Appkit -L libft/ -lft
	$(COMPILERC) -o $(NAME) $(OBJECTS) $(INCLUDES) -L minilibx/ -lmlx -L libft/ -lft -lX11 -lXext
$(LIBFT): libft/*.c libft/*.h	
	@make -C libft/

$(MINILIBX): minilibx_macos/*.c minilibx_macos/*.h
	@make -C minilibx_macos/

%.o: %.c $(HEADER)
	$(COMPILERC) $(FLAGS) $(INCLUDES) -o $@ -c $< 

clean:
	@rm -f $(OBJECTS)
	@make -C libft/ clean
	@make -C minilibx_macos/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@make -C minilibx_macos/ clean

re: fclean all