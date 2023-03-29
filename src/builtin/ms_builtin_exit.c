/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:54:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 21:15:36 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	ms_builtin_exit(t_data *data, char **args)
{
	size_t			args_len;
	long long int	llong_exit_code;
	int				exit_code;

	if (!data || !args)
		return (FAILURE);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	args_len = ms_strs_len(args);
	if (args_len == 0)
		ms_exit(data, g_exit_code);
	else if (!ms_str_is_llong(args[0]))
	{
		ms_error("exit", args[0], "numeric argument required");
		ms_exit(data, MISUSE);
	}
	else if (args_len > 1)
	{
		ms_error("exit", NULL, "too many arguments");
		return (FAILURE);
	}
	llong_exit_code = ms_str_to_llong(args[0]);
	exit_code = (int)(llong_exit_code % 256);
	exit_code = (exit_code + 256) % 256;
	ms_exit(data, exit_code);
	return (SUCCESS);
}
