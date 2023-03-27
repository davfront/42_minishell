/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:04:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/27 16:04:13 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_chdir(t_list **env_list, char *dir)
{
	int		ret;
	char	*oldpwd;
	char	pwd[PATH_MAX];

	if (!dir)
		return (FAILURE);
	ret = chdir(dir);
	if (ret == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(dir, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(NULL);
		return (FAILURE);
	}
	oldpwd = ms_env_list_get(env_list, "PWD");
	ms_env_list_set(env_list, "OLDPWD", oldpwd);
	getcwd(pwd, sizeof(pwd));
	ms_env_list_set(env_list, "PWD", pwd);
	return (SUCCESS);
}

int	ms_cd_home(t_list **env_list)
{
	char	*dir;

	if (!env_list)
		return (FAILURE);
	dir = ms_env_list_get(env_list, "HOME");
	if (!dir)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (FAILURE);
	}
	return (ms_chdir(env_list, dir));
}

int	ms_cd_from_home(t_list **env_list, char *dir)
{
	char	*home;
	char	*new_dir;
	int		ret;

	if (!env_list || !dir || ft_strncmp(dir, "~/", 2) != 0)
		return (FAILURE);
	home = ms_env_list_get(env_list, "HOME");
	if (!home)
		new_dir = ft_strdup(dir + 1);
	new_dir = ft_strjoin(home, dir + 1);
	ret = ms_chdir(env_list, new_dir);
	ft_free((void **)&new_dir);
	return (ret);
}

int	ms_cd_oldpwd(t_list **env_list)
{
	char	*dir;

	if (!env_list)
		return (FAILURE);
	dir = ms_env_list_get(env_list, "OLDPWD");
	if (!dir)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (FAILURE);
	}
	if (ms_chdir(env_list, dir) != SUCCESS)
		return (FAILURE);
	return (ms_pwd());
}

int	ms_cd(t_list **env_list, char **args)
{
	size_t	args_len;
	char	*dir;

	if (!env_list || !args)
		return (FAILURE);
	args_len = ms_strs_len(args);
	if (args_len > 1)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (FAILURE);
	}
	dir = args[0];
	if (!dir || ft_streq(dir, "~") || ft_strncmp(dir, "--", 2) == 0)
		return (ms_cd_home(env_list));
	if (ft_strncmp(dir, "~/", 2) == 0)
		return (ms_cd_from_home(env_list, dir));
	else if (ft_streq(dir, "-"))
		return (ms_cd_oldpwd(env_list));
	return (ms_chdir(env_list, dir));
}
