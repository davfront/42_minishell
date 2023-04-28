/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:59:29 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/28 13:12:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_env_to_char(t_env *env)
{
	size_t	len_label;
	size_t	len_value;
	size_t	len;
	char	*s;

	if (!env || !env->label)
		return (NULL);
	len_label = ft_strlen(env->label);
	len_value = 0;
	if (env->value)
		len_value = ft_strlen(env->value);
	len = len_label + len_value + 1;
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_memcpy(s, env->label, len_label);
	*(s + len_label) = '=';
	if (env->value)
		ft_memcpy(s + len_label + 1, env->value, len_value);
	*(s + len) = '\0';
	return (s);
}

static size_t	ms_env_list_export_size(t_list *env_list)
{
	t_list	*node;
	t_env	*env;
	size_t	i;

	if (!env_list)
		return (0);
	node = env_list;
	i = 0;
	while (node)
	{
		env = (t_env *)(node->content);
		if (env->export)
			i++;
		node = node->next;
	}
	return (i);
}

char	**ms_env_list_export(t_list *env_list)
{
	t_list	*node;
	t_env	*env;
	char	**envp;
	size_t	i;

	envp = ft_calloc(ms_env_list_export_size(env_list) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	node = env_list;
	i = 0;
	while (node)
	{
		env = (t_env *)(node->content);
		if (env->export)
		{
			envp[i] = ms_env_to_char(env);
			if (!envp[i])
				return (ft_free_split(envp), NULL);
			i++;
		}
		node = node->next;
	}
	envp[i] = NULL;
	return (envp);
}
