/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:09:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 18:26:01 by dapereir         ###   ########.fr       */
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

static t_list	*ms_builtin_export_find_alpha_next(t_list **env_list, \
char *prev_label)
{
	t_list	*found;
	char	*found_label;
	t_list	*node;
	t_env	*env;

	found = NULL;
	found_label = NULL;
	node = *env_list;
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

static void	ms_builtin_export_no_arg(t_list **env_list)
{
	t_list	*node;
	t_env	*env;

	node = ms_builtin_export_find_alpha_next(env_list, NULL);
	while (node)
	{
		env = (t_env *)(node->content);
		if (env->value)
			printf("declare -x %s=%s\n", env->label, env->value);
		else
			printf("declare -x %s\n", env->label);
		node = ms_builtin_export_find_alpha_next(env_list, env->label);
	}
}

static int	ms_builtin_export_one(t_list **env_list, char *arg)
{
	t_env	*env;
	int		ret;

	if (!env_list || !*arg)
		return (FAILURE);
	env = ms_env_from_char(arg);
	if (!env)
		return (FAILURE);
	if (!ms_env_is_valid_identifier(env->label))
	{
		ms_builtin_export_print_identifier_error(env->label, env->value);
		ret = FAILURE;
	}
	else
		ret = ms_env_list_set(env_list, env->label, env->value);
	ms_env_delete(env);
	return (ret);
}

int	ms_builtin_export(t_list **env_list, char **args)
{
	size_t	i;
	int		ret;

	if (!env_list)
		return (FAILURE);
	if (!args || !*args)
	{
		ms_builtin_export_no_arg(env_list);
		return (SUCCESS);
	}
	ret = SUCCESS;
	i = 0;
	while (args[i])
	{
		if (ms_builtin_export_one(env_list, args[i]) != SUCCESS)
			ret = FAILURE;
		i++;
	}
	return (ret);
}
