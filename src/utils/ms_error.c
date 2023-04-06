/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:54:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/17 05:56:08 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_str_add_error_arg(char **s, char *arg)
{
	if (!s)
		return ;
	if (arg)
	{
		ms_str_add(s, ": ");
		ms_str_add(s, arg);
	}
}

void	ms_error(char *msg)
{
	char	*s;

	if (!msg)
		return ;
	s = ft_strdup("minishell: ");
	ms_str_add(&s, msg);
	ms_str_add(&s, "\n");
	if (s)
		ft_putstr_fd(s, STDERR_FILENO);
	ft_free((void **)&s);
}

void	ms_error2(char *msg1, char *msg2)
{
	char	*s;

	if (!msg1 && !msg2)
		return ;
	s = ft_strdup("minishell");
	ms_str_add_error_arg(&s, msg1);
	ms_str_add_error_arg(&s, msg2);
	ms_str_add(&s, "\n");
	if (s)
		ft_putstr_fd(s, STDERR_FILENO);
	ft_free((void **)&s);
}

void	ms_error3(char *msg1, char *msg2, char *msg3)
{
	char	*s;

	if (!msg1 && !msg2 && !msg3)
		return ;
	s = ft_strdup("minishell");
	ms_str_add_error_arg(&s, msg1);
	ms_str_add_error_arg(&s, msg2);
	ms_str_add_error_arg(&s, msg3);
	ms_str_add(&s, "\n");
	if (s)
		ft_putstr_fd(s, STDERR_FILENO);
	ft_free((void **)&s);
}

void	ms_error_exit(t_data *data, char *msg, int exit_code)
{
	ms_error(msg);
	ms_exit(data, exit_code);
}
