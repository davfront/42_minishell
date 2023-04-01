/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:09:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 21:18:29 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_unset(t_data *data, char **args)
{
	if (!data || !args || !*args)
		return ;
	while (*args)
	{
		ms_env_list_unset(&(data->env_list), *args);
		args++;
	}
}
