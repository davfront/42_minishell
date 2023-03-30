/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:28:19 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/27 14:39:56 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

typedef struct s_split
{
    int     i;
    int     q_index;
    int     arr_index;
    int     quotes;
    int     len;
}   t_split;

typedef struct s_cmd
{
    char                **cmd;
    int                 infile;
    int                 outfile;
    struct  s_cmd       *next;
}   t_cmd;

# define SUCCESS			0
# define FAILURE			1

typedef struct s_env {
	char	*label;
	char	*value;
}				t_env;

// utils
size_t	ms_strs_len(char **strs);

// env
t_env	*ms_env_new(char *label, char *value);
t_env	*ms_env_from_char(char *s);
void	ms_env_delete(void *content);
int		ms_env_list_add(t_list **env_list, t_env *env);
int		ms_env_list_init(t_list **env_list, char **envp);
void	ms_env_list_clear(t_list **env_list);
t_list	*ms_env_list_find(t_list *env_list, char *label);
void	ms_env_list_delete(t_list **env_list, t_list *node);
int		ms_env_is_valid_identifier(char *name);
int		ms_env_list_update(t_list *node, char *value);
char	*ms_env_list_get(t_list **env_list, char *label);
int		ms_env_list_set(t_list **env_list, char *label, char *value);
void	ms_env_list_unset(t_list **env_list, char *label);

// builtin
int		ms_pwd(void);
void	ms_echo(char **args);
void	ms_env(t_list **env_list);
void	ms_unset(t_list **env_list, char **args);
int		ms_export(t_list **env_list, char **args);
int		ms_cd(t_list **env_list, char **args);

// parsing
char	**ms_parser(char *line);
char    **ms_cmdsplit(char *str, char *set);

#endif
