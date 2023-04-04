/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:28:19 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/04 17:41:53 by lboulatr         ###   ########.fr       */
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

# define LLONG_MAX_STR	"9223372036854775807"

# define SUCCESS			EXIT_SUCCESS
# define FAILURE			EXIT_FAILURE
# define MISUSE				2

extern int	g_exit_code;

typedef struct s_split
{
	int	i;
	int	q_index;
	int	arr_index;
	int	quotes;
	int	dollar;
	int	len;
}	t_split;

typedef struct s_env {
	char	*label;
	char	*value;
}	t_env;

typedef struct s_data {
	t_list	*env_list;
	char	*line;
	char	**tokens;
}	t_data;

// utils
size_t		ms_strs_len(char **strs);
int			ms_str_is_llong(char *s);
long long	ms_str_to_llong(char *str);
void		ms_error(char *cmd, char *arg, char *msg);
void		ms_exit(t_data *data, int exit_code);
void		ms_init(t_data *data, char **envp);
void		ms_reset(t_data *data);

// utils
void		ms_print_quoted(char *s);

// env
t_env		*ms_env_new(char *label, char *value);
t_env		*ms_env_from_char(char *s);
void		ms_env_delete(void *content);
int			ms_env_list_add(t_list **env_list, t_env *env);
int			ms_env_list_init(t_list **env_list, char **envp);
void		ms_env_list_clear(t_list **env_list);
t_list		*ms_env_list_find(t_list *env_list, char *label);
void		ms_env_list_delete(t_list **env_list, t_list *node);
int			ms_env_is_valid_identifier(char *name);
int			ms_env_list_update(t_list *node, char *value);
char		*ms_env_list_get(t_list **env_list, char *label);
int			ms_env_list_set(t_list **env_list, char *label, char *value);
void		ms_env_list_unset(t_list **env_list, char *label);

//	 builtin
int			ms_builtin_pwd(void);
void		ms_builtin_echo(char **args);
void		ms_builtin_env(t_data *data);
void		ms_unset(t_data *data, char **args);
int			ms_builtin_export(t_data *data, char **args);
int			ms_builtin_cd(t_data *data, char **args);
int			ms_builtin_exit(t_data *data, char **args);
int			ms_is_builtin_cmd(char *cmd);
int			ms_builtin_cmd(t_data *data, char **cmd_args);

// parsing
char		**ms_parser(char *line, t_data *data);
char		**ms_var_array(char *str, char **var_array, t_list *env);
char		**ms_cmdsplit(char *str, char *set);

// expand
char		*ms_expand_var(char *str, t_list *env);
int			ms_content_len(int index, char *str);
int			ms_count_var(char *str);
char		*ms_tilde(char *str, t_list *env);
int			ms_char_print(char c);
int			ms_char_nprint(char c);
int			ms_dollar_is_valid(char c);

// parsing utils
int			ms_is_quote(char c);
void		ms_free_and_exit(char *str);
void		ms_free_array(char **array);
char		*ms_get_exit_code(int exit_code);

void		printarr(char **cmd);

#endif
