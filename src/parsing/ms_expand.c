/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:43:18 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/21 11:34:39 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_expand(t_data *data)
{
	if (!data || !data->line)
		return (FAILURE);
	data->line = ms_expand_var(data->line, data);
	if (!data->line)
		return (FAILURE);
	data->line = ms_tilde(data->line, data);
	if (!data->line)
		return (FAILURE);
	return (SUCCESS);
}
