/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_builtin_cmd_no_fork.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/09 16:02:02 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_builtin_cmd_no_fork(char *cmd)
{
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
