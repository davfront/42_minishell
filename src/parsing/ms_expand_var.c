/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osterger <osterger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:58:58 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/06 02:33:24 by osterger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ms_change_line(char *tmp, int *index, t_data *data);
static char	*ms_get_after_dollar(char *dollar);

char	*ms_expand_var(char *str, t_data *data)
{
	int		i;
	char	*copy_str;
	
	i = 0;
	copy_str = ft_strdup(str);
	if (!copy_str)
		return (NULL);
	while (copy_str[i])
	{
		if (copy_str[i] == '$' && !ms_is_char_print(copy_str[i + 1]))
		{
			copy_str = ms_change_line(copy_str, &i, data);
			if (!copy_str)
				return (NULL);
		}
		else
			i++;
	}
	return (copy_str);
}

static char *ms_change_line(char *tmp, int *index, t_data *data)
{
	char	*before;
	char	*after;
	char	*var_name;
	char	*var_content;
	char	*expanded_str;
	int		i;

	i = *index;
	before = ft_substr(tmp, 0, i);
	if (tmp[i + 1] == '?')
		after = &tmp[i + 2];
	else if (ft_isalnum(tmp[i + 1]) || ms_is_char_nprint(tmp[i + 1]))
		after = ms_get_after_dollar(tmp + i + 1);
	var_name = ms_get_var_name(tmp, i + 1);
	var_content = ms_env_list_get(&(data->env_list), var_name);
	expanded_str = ms_join(before, var_content, after);
	if (var_content)
		(*index) += ft_strlen(var_content);
	ft_free((void **)&before);
	ft_free((void **)&var_name);
	return (expanded_str);
}

static char	*ms_get_after_dollar(char *dollar)
{
	int		i;

	i = 0;
	if (dollar[i] == '{')
		i++;
	if (ms_is_char_nprint(dollar[i]))
	{
		while (dollar[i] && ms_is_char_nprint(dollar[i]))
			i++;
		return (&dollar[i]);
	}
	while (dollar[i] && (ft_isalnum(dollar[i]) || dollar[i] == '_'))
		i++;
	if (dollar[i] == '}')
		i++;
	return (&dollar[i]);
}
