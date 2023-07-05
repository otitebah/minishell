/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:57:25 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/24 18:34:36 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5

# endif

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

enum				e_definitions
{
	CMD = 0,
	INPUT = 1,
	OUTPUT = 2,
	L_OP = 3,
	R_OP = 4,
	APPEND = 5,
	HEREDOC = 6,
	PIPE = 7,
	ARG = 8,
	DELIMITER = 9,
};

typedef struct s_token
{
	int				type;
	int				av_quotes;
	char			*data;
	struct s_token	*next;
}					t_token;

typedef struct s_args
{
	char			**args;
	int				infile;
	int				outfile;
	struct s_args	*next;
}					t_args;

typedef struct s_var
{
	char			*str;
	char			*str2;
	int				y;
	int				lock;
	int				check;
	int				*x;
	char			*line;
	int				quotes_check;
}					t_var;

typedef struct s_var2
{
	char			*to_expand;
	char			*expanded;
	int				y;
	int				check1;
	int				check2;
	int				check3;
	int				j;
	int				i;
	char			*str;
	int				p;
	int				check;
}					t_var2;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

void				ft_lstadd_back(t_token **lst, t_token *new);
void				ft_lstadd_back2(t_args **lst, t_args *new);
t_token				*ft_lstlast(t_token *lst);
t_token				*ft_lstnew(char *data);
t_args				*ft_lstnew2(void);
char				*ft_strdup(const char *s1);
t_args				*ft_lstlast2(t_args *lst);
int					create_list(t_args **args, t_token *token);
int					args_count(t_token *lst);
void				check_in_out(t_args *args, int in, int out);
int					heredoc(t_args *args, char *delimiter, t_env *env_parse,
						t_token *lst);
char				*get_next_line(int fd);
int					ft_strcmp(const char *s1, const char *s2);
int					check_quotes(t_token **lst, char *line, int *x,
						t_env *env_parse);
int					lexing(char *line, t_token **lst, int *x, t_env *env_parse);
int					lexing2(char *line, t_token **lst, int *x);
int					lexing3(t_token **lst);
int					split_args(t_token *lst, t_args **args, t_env *env_parse);
char				*ft_chrjoin(char *s1, char c2);
char				*expand(t_token *lst, char *line, int *x, t_env *env_parse);
int					errors_check(t_token *lst);
void				rl_replace_line(const char *text, int clear_undo);
char				*heredoc_expand(char *line, t_env *env_parse, int x);
int					split_args2(t_token *temp, t_args **args, t_token *lst,
						t_env *env_parse);
void				split_args3(t_token *temp, t_args **args, int *in,
						int *out);
void				handler2(int num);
char				*ft_join_free(char *s1, char *s2);
int					check_quotes_follow(char *line, int *x, t_token **lst);
void				check_quotes_follow2(int *x, t_token **lst,
						t_env *env_parse, t_var *var);
void				check_quotes3(t_env *env_parse, char *str);
int					check_quotes_follow4(int *x, t_token **lst,
						t_env *env_parse, t_var *var);
void				check_quotes_follow5(int *x, t_token **lst,
						t_env *env_parse, t_var *var);
int					check_quotes_follow6(int *x, t_token **lst,
						t_env *env_parse, t_var *var);
char				*check_quotes4(t_token **lst,
						t_var *var, int *x, char *str);
void				expand6(t_var2 *var2);
void				check_quotes5(t_var *var, t_token *lst, char *str);

/**********/

#endif