/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:28:19 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/28 17:55:11 by lboulatr         ###   ########.fr       */
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

typedef struct s_trim
{
    int     i;
    int     j;
    int     k;
    int     quotes;
    int     len;
}   t_trim;

typedef struct s_cmd
{
    char                **cmd;
    int                 infile;
    int                 outfile;
    struct  s_cmd       *next;
}   t_cmd;

// builtin
void	ms_pwd(void);
void	ms_echo(char **args);

// parsing
int         ms_parser(char *line);
char        **ms_cmdtrim(char *str, char *set);
void        del_char(char *str, char c);
int	        check_char_option(int c);
int         is_option(char *str);
void        ms_clean_commands(char **cmds);
void        check_dollar(char **cmds, int i, int j);
char        **create_cmd_init(char **array, int count);
int         count_pipe(char *str);
//void         command_list_init(char **array, int n_pipe);
int         count_items_cmd(char **array, int *i);
//t_cmd       *new_cmd(char **array, int count, int *j);
void        create_list(char **array, int n_pipe);
int         ft_index(char **array);


void        printarr(char **arr);
#endif