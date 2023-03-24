/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:28:19 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/24 15:09:49 by lboulatr         ###   ########.fr       */
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

typedef enum    e_type
{
    NONE = -1,
    CMD = 0,
    OPTION,
    ARG,
    PIPE,
    GREATER,
    G_GREATER,
    LESS,
    L_LESS
}   t_type;

typedef struct s_cmd
{
    int                 status;
    char                **cmd;
    struct s_cmd       *next;
}   t_cmd;

typedef struct s_item
{
    char                *value;
    t_type              type;
    struct s_item      *next;
}   t_item;

// builtin
void	ms_pwd(void);
void	ms_echo(char **args);

// parsing
void    parser(char *line);

#endif
