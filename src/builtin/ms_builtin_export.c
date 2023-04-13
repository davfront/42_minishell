/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:09:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 22:57:03 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_builtin_export_print_identifier_error(char *label, char *value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(label, STDERR_FILENO);
	ft_putstr_fd("=", STDERR_FILENO);
	ft_putstr_fd(value, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static t_list	*ms_builtin_export_find_alpha_next(t_data *data, \
char *prev_label)
{
	t_list	*found;
	char	*found_label;
	t_list	*node;
	t_env	*env;

	found = NULL;
	found_label = NULL;
	node = data->env_list;
	while (node)
	{
		env = (t_env *)(node->content);
		if ((!prev_label || \
			ft_strncmp(env->label, prev_label, ft_strlen(env->label) + 1) > 0) \
			&& (!found_label || \
			ft_strncmp(env->label, found_label, ft_strlen(env->label) + 1) < 0))
		{
			found = node;
			found_label = env->label;
		}
		node = node->next;
	}
	return (found);
}

static void	ms_builtin_export_no_arg(t_data *data)
{
	t_list	*node;
	t_env	*env;

	node = ms_builtin_export_find_alpha_next(data, NULL);
	while (node)
	{
		env = (t_env *)(node->content);
		if (env->export)
		{
			ft_putstr("declare -x ");
			ft_putstr(env->label);
			if (env->value)
			{
				ft_putstr("=");
				ms_print_quoted(env->value);
			}
			ft_putstr("\n");
		}
		node = ms_builtin_export_find_alpha_next(data, env->label);
	}
}

static int	ms_builtin_export_one(t_data *data, char *arg)
{
	t_env	*env;
	int		ret;

	if (!data || !*arg)
		return (FAILURE);
	env = ms_env_from_char(arg, 1);
	if (!env)
		return (FAILURE);
	if (!ms_env_is_valid_identifier(env->label))
	{
		ms_builtin_export_print_identifier_error(env->label, env->value);
		ret = FAILURE;
	}
	else
		ret = ms_env_list_set(&(data->env_list), \
			env->label, env->value, env->export);
	ms_env_delete(env);
	return (ret);
}

int	ms_builtin_export(t_data *data, char **args)
{
	size_t	i;
	int		ret;

	if (!data)
		return (FAILURE);
	if (!args || !*args)
	{
		ms_builtin_export_no_arg(data);
		return (SUCCESS);
	}
	ret = SUCCESS;
	i = 0;
	while (args[i])
	{
		if (ms_builtin_export_one(data, args[i]) != SUCCESS)
			ret = FAILURE;
		i++;
	}
	return (ret);
}
