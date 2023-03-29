/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:09:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/25 11:31:08 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_unset(t_list **env_list, char **args)
{
	if (!env_list || !*env_list || !args || !*args)
		return ;
	while (*args)
	{
		ms_env_list_unset(env_list, *args);
		args++;
	}
}