/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_declare_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:21:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 22:57:18 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_cmd_declare_var(t_data *data, char *arg)
{
	t_env	*env;
	int		ret;

	if (!data || !*arg)
		return (FAILURE);
	env = ms_env_from_char(arg, 0);
	if (!env)
		return (FAILURE);
	if (!ms_env_is_valid_identifier(env->label))
		ret = FAILURE;
	else
		ret = ms_env_list_set(&(data->env_list), \
			env->label, env->value, env->export);
	ms_env_delete(env);
	return (ret);
}

int	ms_cmd_declare_vars(t_data *data, t_cmd *cmd)
{
	size_t	i;

	if (!data || !data->env_list || !cmd || !cmd->tokens)
		return (FAILURE);
	i = 0;
	while (!ms_token_is_cmd_sep(cmd->tokens[i]))
	{
		if (cmd->tokens[i].type == VARSET)
		{
			if (ms_cmd_declare_var(data, cmd->tokens[i].str) != SUCCESS)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
