/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:15:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/21 07:18:21 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_expand2(t_data *data)
{
	if (!data || !data->line)
		return (FAILURE);
	if (ms_expand2_exit_code(data, &(data->line)) != SUCCESS)
		return (FAILURE);
	if (ms_expand2_vars(&(data->line), &(data->env_list)) != SUCCESS)
		return (FAILURE);
	if (ms_expand2_tilde(&(data->line), &(data->env_list)) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
