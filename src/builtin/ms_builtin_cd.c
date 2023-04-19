/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:04:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 22:20:28 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_chdir(t_data *data, char *dir)
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
	oldpwd = ms_env_list_get(&(data->env_list), "PWD");
	ms_env_list_set(&(data->env_list), "OLDPWD", oldpwd, 1);
	getcwd(pwd, sizeof(pwd));
	ms_env_list_set(&(data->env_list), "PWD", pwd, 1);
	return (SUCCESS);
}

static int	ms_builtin_cd_home(t_data *data)
{
	char	*dir;

	if (!data)
		return (FAILURE);
	dir = ms_env_list_get(&(data->env_list), "HOME");
	if (!dir)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (FAILURE);
	}
	return (ms_chdir(data, dir));
}

static int	ms_builtin_cd_from_home(t_data *data, char *dir)
{
	char	*home;
	char	*new_dir;
	int		ret;

	if (!data || !dir || ft_strncmp(dir, "~/", 2) != 0)
		return (FAILURE);
	home = ms_env_list_get(&(data->env_list), "HOME");
	if (!home)
		new_dir = ft_strdup(dir + 1);
	new_dir = ft_strjoin(home, dir + 1);
	ret = ms_chdir(data, new_dir);
	ft_free((void **)&new_dir);
	return (ret);
}

static int	ms_builtin_cd_oldpwd(t_data *data)
{
	char	*dir;

	if (!data)
		return (FAILURE);
	dir = ms_env_list_get(&(data->env_list), "OLDPWD");
	if (!dir)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (FAILURE);
	}
	if (ms_chdir(data, dir) != SUCCESS)
		return (FAILURE);
	return (ms_builtin_pwd());
}

int	ms_builtin_cd(t_data *data, char **args)
{
	size_t	args_len;
	char	*dir;

	if (!data || !args)
		return (FAILURE);
	args_len = ms_strs_len(args);
	if (args_len > 1)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (FAILURE);
	}
	dir = args[0];
	if (!dir || ft_streq(dir, "~") || ft_strncmp(dir, "--", 2) == 0)
		return (ms_builtin_cd_home(data));
	if (ft_strncmp(dir, "~/", 2) == 0)
		return (ms_builtin_cd_from_home(data, dir));
	else if (ft_streq(dir, "-"))
		return (ms_builtin_cd_oldpwd(data));
	return (ms_chdir(data, dir));
}
