/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_script_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/09 15:41:05 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_script_cmd(char *cmd)
{
	char	*slash;
	char	*equal;

	if (!cmd || !*cmd)
		return (0);
	slash = ft_strchr(cmd, '/');
	equal = ft_strchr(cmd, '=');
	return (slash && (!equal || equal > slash));
}
