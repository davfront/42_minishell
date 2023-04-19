/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/22 16:22:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_env_list_init_from_envp(t_list **env_list, char **envp)
{
	t_env	*env;

	if (!envp)
		return (FAILURE);
	while (*envp)
	{
		env = ms_env_from_char(*envp);
		if (!env || ms_env_list_add(env_list, env) != SUCCESS)
		{
			ms_env_list_clear(env_list);
			return (FAILURE);
		}
		envp++;
	}
	return (SUCCESS);
}

static int	ms_env_list_init_pwd(t_list **env_list)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, sizeof(pwd)))
		return (FAILURE);
	return (ms_env_list_set(env_list, "PWD", pwd));
}

static int	ms_env_list_init_path(t_list **env_list)
{
	if (ms_env_list_get(env_list, "PATH"))
		return (SUCCESS);
	return (ms_env_list_set(env_list, "PATH", "/usr/local/bin:/usr/bin:/bin"));
}

static int	ms_env_list_init_shlvl(t_list **env_list)
{
	char	*shlvl_str;
	int		shlvl;
	int		ret;

	shlvl_str = ms_env_list_get(env_list, "SHLVL");
	if (!shlvl_str)
		return (ms_env_list_set(env_list, "SHLVL", "1"));
	shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		shlvl = -1;
	if (shlvl >= 999)
		shlvl = 0;
	shlvl_str = ft_itoa(shlvl + 1);
	if (!shlvl_str)
		return (FAILURE);
	ret = ms_env_list_set(env_list, "SHLVL", shlvl_str);
	ft_free((void **)&shlvl_str);
	return (ret);
}

int	ms_env_list_init(t_list **env_list, char **envp)
{
	if (ms_env_list_init_from_envp(env_list, envp) != SUCCESS)
		return (FAILURE);
	if (ms_env_list_init_pwd(env_list) != SUCCESS)
		return (FAILURE);
	if (ms_env_list_init_path(env_list) != SUCCESS)
		return (FAILURE);
	if (ms_env_list_init_shlvl(env_list) != SUCCESS)
		return (FAILURE);
	ms_env_list_unset(env_list, "_");
	return (SUCCESS);
}
