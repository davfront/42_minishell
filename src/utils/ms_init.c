/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:42:44 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 21:07:05 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_init_default(t_data *data)
{
	if (!data)
		return ;
	data->env_list = NULL;
	data->line = NULL;
	data->tokens = NULL;
}

void	ms_init(t_data *data, char **envp)
{
	if (!data)
		return ;
	ms_init_default(data);
	ms_env_list_init(&(data->env_list), envp);
}
