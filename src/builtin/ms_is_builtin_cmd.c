/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_builtin_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:31:04 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 18:11:41 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_builtin_cmd(char *cmd)
{
	if (ft_streq(cmd, "pwd"))
		return (1);
	if (ft_streq(cmd, "echo"))
		return (1);
	if (ft_streq(cmd, "env"))
		return (1);
	if (ft_streq(cmd, "export"))
		return (1);
	if (ft_streq(cmd, "unset"))
		return (1);
	if (ft_streq(cmd, "cd"))
		return (1);
	if (ft_streq(cmd, "exit"))
		return (1);
	return (0);
}
