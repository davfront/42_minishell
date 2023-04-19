/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:54:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/09 17:08:18 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_print_error_arg(char *arg)
{
	if (arg)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
	}
}

void	ms_error(char *msg)
{
	if (msg)
		ft_putstr_fd("minishell", STDERR_FILENO);
	ms_print_error_arg(msg);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	ms_error2(char *msg1, char *msg2)
{
	if (msg1 || msg2)
		ft_putstr_fd("minishell", STDERR_FILENO);
	ms_print_error_arg(msg1);
	ms_print_error_arg(msg2);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	ms_error3(char *msg1, char *msg2, char *msg3)
{
	if (msg1 || msg2 || msg3)
		ft_putstr_fd("minishell", STDERR_FILENO);
	ms_print_error_arg(msg1);
	ms_print_error_arg(msg2);
	ms_print_error_arg(msg3);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	ms_error_exit(t_data *data, char *msg, int exit_code)
{
	ms_error(msg);
	ms_exit(data, exit_code);
}
