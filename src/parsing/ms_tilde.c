/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:09:23 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/21 03:32:18 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_change_line(char *str, int i, t_data *data);
static char	*ms_cut_line(char *str, int i, char *home);

char	*ms_tilde(char *str, t_data *data)
{
	int		i;
	char	*copy_str;
	char	*new_str;

	i = 0;
	copy_str = ft_strdup(str);
	if (!copy_str)
		return (NULL);
	while (copy_str[i])
	{
		if (copy_str[i] == '~' && ft_strchr("/: \0", copy_str[i + 1]))
		{
			new_str = ms_change_line(copy_str, i, data);
			ft_free((void **)&copy_str);
			copy_str = new_str;
		}
		i++;
	}
	return (copy_str);
}

static char	*ms_change_line(char *str, int i, t_data *data)
{
	char	*home;
	char	*expanded_str;

	home = ms_env_list_get(&(data->env_list), "HOME");
	if (!home)
		return (NULL);
	expanded_str = ms_cut_line(str, i, home);
	return (expanded_str);
}

static char	*ms_cut_line(char *str, int i, char *home)
{
	char	*copy_str;
	char	*before;
	char	*after;
	char	*expanded_tilde_str;

	copy_str = ft_strdup(str);
	if (!copy_str)
		return (NULL);
	before = ft_substr(copy_str, 0, i);
	if (!before)
	{
		ft_free((void **)&copy_str);
		return (NULL);
	}
	after = &copy_str[i + 1];
	expanded_tilde_str = ms_join3(before, home, after);
	ft_free((void **)&before);
	ft_free((void **)&copy_str);
	return (expanded_tilde_str);
}