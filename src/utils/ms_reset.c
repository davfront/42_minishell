/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:42:44 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 21:02:10 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_reset(t_data *data)
{
	if (!data)
		return ;
	ms_env_list_clear(&(data->env_list));
	ft_free((void **)&(data->line));
	ft_free_split(data->tokens);
}
