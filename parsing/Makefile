# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 21:04:40 by machaiba          #+#    #+#              #
#    Updated: 2023/06/23 02:55:33 by machaiba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = minishell.c\
		ft_lstadd_back.c\
		ft_lstnew.c\
		ft_lstlast.c\
		ft_strlen.c\
		create_list.c\
		args_count.c\
		check_in_out.c\
		get_next_line.c\
		get_next_line_utils.c\
		heredoc.c\
		ft_strcmp.c\
		check_quotes.c\
		ft_chrjoin.c\
		expand.c\
		errors_check.c\
		lexing2.c\
		split_args.c\
		split_args2.c\
		split_args3.c\
		heredoc_expand.c\
		ft_join_free.c\
		check_quotes_follow.c\
		expand2.c\
	
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

INCLUDES = ../libft/libft.a

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		make -C ../libft	
		cc $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME) -ledit

clean :
		rm -rf $(OBJS)
		rm -rf ../libft/*.o

fclean : clean
		rm -rf $(NAME)
		rm -rf ../libft/*.a

re : fclean all