/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:54:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 17:46:20 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_error(char *cmd, char *arg, char *msg)
{
	if (cmd || arg || msg)
		ft_putstr_fd("minishell", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
	}
	if (msg)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}
