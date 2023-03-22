/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/22 19:47:20 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env_delete(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	if (!env)
		return ;
	ft_free((void **)&(env->label));
	ft_free((void **)&(env->value));
	ft_free((void **)&env);
}
