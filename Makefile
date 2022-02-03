# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 10:08:29 by ngobert           #+#    #+#              #
#    Updated: 2022/02/03 09:57:44 by ngobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SV = server
NAME_CL = client

SRCS_SV = server.c print_menu.c
SRCS_CL = client.c
OBJS_SV = $(SRCS_SV:.c=.o)
OBJS_CL = $(SRCS_CL:.c=.o)

GCC_FLAG = -Wall -Werror -Wextra
CC = gcc $(GCC_FLAG)

all: $(NAME_SV) $(NAME_CL)

libft:
	make bonus -C libft/
	make -C libft/ft_printf/

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME_SV): $(OBJS_SV)
	make -C libft bonus
	make -C libft/ft_printf
	$(CC) -o $@ $(OBJS_SV) libft/libft.a libft/ft_printf/libftprintf.a

$(NAME_CL): libft $(OBJS_CL)
	$(CC) -o $@ $(OBJS_CL) libft/libft.a libft/ft_printf/libftprintf.a

clean:
	rm -f *.o
	rm -f *.o
	make -C libft/ clean
	make -C libft/ft_printf clean

fclean: clean
	rm -f $(NAME_SV) $(NAME_CL)
	make -C libft/ fclean
	make -C libft/ft_printf/ fclean

re: fclean all
