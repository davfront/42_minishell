/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/25 12:13:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env_list_add(t_list **env_list, t_env *env)
{
	t_list	*new;

	if (!env_list || !env)
		return (FAILURE);
	new = ft_lstnew(env);
	if (!new)
		return (FAILURE);
	ft_lstadd_back(env_list, new);
	return (SUCCESS);
}
