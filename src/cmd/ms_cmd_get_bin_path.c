/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_get_bin_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:22:38 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/09 18:11:45 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ms_append_backslash_to_pathes(char **pathes)
{
	size_t	i;
	char	*new_path;

	if (!pathes)
		return (NULL);
	i = 0;
	while (pathes[i])
	{
		new_path = ft_strjoin(pathes[i], "/");
		if (!new_path)
		{
			ms_error("ft_strjoin failed");
			return (ft_free_split(pathes), NULL);
		}
		ft_free((void **)(pathes + i));
		pathes[i] = new_path;
		i++;
	}
	return (pathes);
}

static char	**ms_cmd_get_env_pathes(t_data *data)
{
	char	*env_path;
	char	**env_pathes;

	if (!data || !data->env_list)
		return (NULL);
	env_path = ms_env_list_get(&(data->env_list), "PATH");
	if (!env_path || !*env_path)
		return (NULL);
	env_pathes = ft_split(env_path, ':');
	if (!env_pathes)
		return (ms_error("ft_split failed"), NULL);
	return (ms_append_backslash_to_pathes(env_pathes));
}

char	*ms_cmd_get_bin_path(t_data *data, char *cmd)
{
	char	**dir_pathes;
	size_t	i;
	char	*bin_path;

	if (!cmd)
		return (NULL);
	dir_pathes = ms_cmd_get_env_pathes(data);
	if (!dir_pathes)
		return (NULL);
	i = 0;
	while (dir_pathes[i])
	{
		bin_path = ft_strjoin(dir_pathes[i], cmd);
		if (!bin_path)
			ms_error("ft_strjoin failed");
		else if (access(bin_path, F_OK) == 0)
			return (ft_free_split(dir_pathes), bin_path);
		ft_free((void **)&bin_path);
		i++;
	}
	ft_free_split(dir_pathes);
	return (NULL);
}
