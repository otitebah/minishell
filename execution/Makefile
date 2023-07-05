# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 12:35:18 by otitebah          #+#    #+#              #
#    Updated: 2023/06/17 19:40:58 by otitebah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FILES = builtins.c ft_strcpy.c save_env.c ft_lstadd_front.c save_export.c\
		commands.c ../parsing/ft_strcmp.c
		
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
INCLUDES = ../libft/libft.a

OBJ = $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C ../libft
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -lreadline -o $(NAME)
	
clean :
	rm -f $(OBJ)
	rm -f ../libft/*.o

fclean : clean
	rm -f $(NAME)
	rm -f ../libft/*.a

re : fclean all

push :
	git add .
	git status
	git commit -m "update!"
	git push