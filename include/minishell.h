/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:28:19 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/19 14:18:30 by dapereir         ###   ########.fr       */
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

# define DEBUG				1

# define LLONG_MAX_STR		"9223372036854775807"

# define SUCCESS			EXIT_SUCCESS
# define FAILURE			EXIT_FAILURE
# define MISUSE				2
# define CANT_EXEC			126
# define NOT_FOUND			127

# define PS1				"\033[1;36mminishell>\033[0m "
# define PS2				"> "

# define CMD_MAX			64

# define HEREDOC_TMP		"heredoc.tmp"

typedef struct s_split
{
	int		i;
	int		q_index;
	int		arr_index;
	int		quotes;
	int		len;
}	t_split;

typedef struct s_env {
	char	*label;
	char	*value;
	int		export;
}	t_env;

typedef enum e_type {
	UNDEFINED = 0,
	PIPE,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APP,
	WORD,
	VARSET,
	END,
}	t_type;

typedef struct s_tok {
	t_type	type;
	char	*str;
}	t_tok;

typedef struct s_cmd {
	t_tok	*tokens;
	char	**args;
	char	**envp;
	char	*exe_path;
	int		fd_in;
	int		fd_out;
}	t_cmd;

typedef struct s_data {
	int		exit_code;
	t_list	*env_list;
	char	*line;
	t_tok	*tokens;
	int		cmd_size;
	t_cmd	*cmds;
	int		*fd_pipe;
	int		heredoc_enabled;
	char	*heredoc_delimiter;
	int		heredoc_fd;
}	t_data;

// utils
size_t		ms_strs_len(char **strs);
int			ms_str_is_llong(char *s);
long long	ms_str_to_llong(char *str);
void		ms_str_add(char **s, char *s2);
void		ms_exit(t_data *data, int exit_code);
void		ms_error(char *msg);
void		ms_error2(char *msg1, char *msg2);
void		ms_error3(char *msg1, char *msg2, char *msg3);
void		ms_error_exit(t_data *data, char *msg, int exit_code);
void		ms_perror(char *msg);
void		ms_perror_exit(t_data *data, char *msg, int exit_code);
int			ms_init(t_data *data, int argc, char **argv, char **envp);
void		ms_reset(t_data *data);
void		ms_reset_prompt(t_data *data);
void		ms_reset_cmds(t_data *data);
void		ms_print_quoted(char *s);
int			ms_fd_is_file(int fd);

// env
t_env		*ms_env_new(char *label, char *value, int export);
t_env		*ms_env_from_char(char *s, int export);
void		ms_env_delete(void *content);
int			ms_env_list_add(t_list **env_list, t_env *env);
int			ms_env_list_init(t_list **env_list, char **envp);
void		ms_env_list_clear(t_list **env_list);
t_list		*ms_env_list_find(t_list *env_list, char *label);
void		ms_env_list_delete(t_list **env_list, t_list *node);
int			ms_env_is_valid_identifier(char *name);
int			ms_env_list_update(t_list *node, char *value, int export);
char		*ms_env_list_get(t_list **env_list, char *label);
int			ms_env_list_set(t_list **env_list, char *label, char *value, \
				int export);
void		ms_env_list_unset(t_list **env_list, char *label);
char		**ms_env_list_export(t_list *env_list);

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

// prompt
char		*ms_read_prompt(void);

// parsing
char		**ms_parser(char *line);
char		**ms_cmdsplit(char *str, char *set);
int			ms_token_is_cmd_sep(t_tok token);
int			ms_token_is_io_sep(t_tok token);
int			ms_token_is_sep(t_tok token);
int			ms_check_tokens(t_tok *tokens);
int			ms_parse_line_to_tokens(t_data *data);
void		ms_tokens_merge_io_args(t_tok *tokens);
void		ms_tokens_type_varset(t_tok *tokens);
void		ms_tokens_remove_quotes(t_tok *tokens);
int			ms_parse_tokens_to_cmds(t_data *data);

// heredoc
int			ms_heredoc_create_tmp(t_data *data);

// cmd
int			ms_is_builtin_cmd_no_fork(char *cmd);
int			ms_is_script_cmd(char *cmd);
int			ms_cmd_init(t_cmd *cmd, t_tok *tokens);
char		*ms_cmd_get_bin_path(t_data *data, char *cmd);
int			ms_cmd_declare_vars(t_data *data, t_cmd *cmd);
int			ms_cmd_open_io_files(t_cmd *cmd);
void		ms_cmd_close_io_files(t_cmd *cmd);

// execute
void		ms_exec_dup2(t_data *data, int fd1, int fd2);
int			ms_exec_pipe(t_data *data);
int			ms_exec_cmds(t_data *data);
void		ms_exec_fork_cmd(t_data *data, t_cmd *cmd);

// signal
void		ms_handle_sigint(int sig);

// debug
void		ms_debug_tokens(t_data *data);
void		ms_debug_exit_code(int exit_code);
void		ms_debug_cmds(t_data *data);

#endif
