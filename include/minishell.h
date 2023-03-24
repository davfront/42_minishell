/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:28:19 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/25 10:38:49 by dapereir         ###   ########.fr       */
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

typedef struct s_env {
	char	*label;
	char	*value;
}				t_env;

// env
t_env	*ms_env_new(char *label, char *value);
t_env	*ms_env_from_char(char *s);
void	ms_env_delete(void *content);
void	ms_env_list_add(t_list **env_list, t_env *env);
void	ms_env_list_init(t_list **env_list, char **envp);
void	ms_env_list_clear(t_list **env_list);
t_list	*ms_env_list_get_by_label(t_list *env_list, char *label);
void	ms_env_list_delete(t_list **env_list, t_list *node);
int		ms_env_is_valid_identifier(char *name);
void	ms_env_list_update(t_list *node, char *value);
void	ms_env_list_set(t_list **env_list, char *label, char *value);
void	ms_env_list_unset(t_list **env_list, char *label);

// builtin
void	ms_env(t_list *env_list);
void	ms_unset(t_list **env_list, char **args);
void	ms_export(t_list **env_list, char **args);

#endif
