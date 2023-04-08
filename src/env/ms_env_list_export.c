/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:59:29 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/09 10:45:59 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_env_to_char(t_env *env)
{
	size_t	len_label;
	size_t	len_value;
	size_t	len;
	char	*s;

	if (!env || !env->label || !env->value)
		return (NULL);
	len_label = ft_strlen(env->label);
	len_value = ft_strlen(env->value);
	len = len_label + len_value + 1;
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_memcpy(s, env->label, len_label);
	*(s + len_label) = '=';
	ft_memcpy(s + len_label + 1, env->value, len_value);
	*(s + len) = '\0';
	return (s);
}

char	**ms_env_list_export(t_list *env_list)
{
	t_list	*node;
	t_env	*env;
	char	**envp;
	size_t	len;
	size_t	i;

	if (!env_list)
		return (NULL);
	len = ft_lstsize(env_list);
	envp = ft_calloc(len + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	node = env_list;
	i = 0;
	while (node)
	{
		env = (t_env *)(node->content);
		envp[i] = ms_env_to_char(env);
		if (!envp[i])
			return (ft_free_split(envp), NULL);
		node = node->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
