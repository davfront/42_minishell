/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:58:58 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/21 09:10:03 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_change_line(char *copy_str, int *index, t_data *data);
static char	*ms_get_after_dollar(char *dollar);

char	*ms_expand_var(char *str, t_data *data)
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
		if (copy_str[i] == '$' && !ms_is_char_print(copy_str[i + 1]))
		{
			if (copy_str[i + 1] == '?')
				new_str = ms_expand_exit_code(copy_str, &i);
			else
				new_str = ms_change_line(copy_str, &i, data);
			if (!new_str)
				return (ft_free((void **)&copy_str), NULL);
			ft_free((void **)&copy_str);
			copy_str = new_str;
		}
		else
			i++;
	}
	return (copy_str);
}

static char	*ms_change_line(char *copy_str, int *index, t_data *data)
{
	char	*before;
	char	*after;
	char	*var_name;
	char	*var_content;
	char	*expanded_str;

	before = ft_substr(copy_str, 0, (int)*index);
	if (!before)
		return (NULL);
	if (ft_isalnum(copy_str[(int)*index + 1]) || \
		ms_is_char_nprint(copy_str[(int)*index + 1]))
		after = ms_get_after_dollar(copy_str + (int)*index + 1);
	var_name = ms_get_var_name(copy_str, (int)*index + 1);
	if (!var_name)
		return (ft_free((void **)&before), NULL);
	var_content = ms_env_list_get(&(data->env_list), var_name);
	expanded_str = ms_join3(before, var_content, after);
	if (var_content)
		(*index) += ft_strlen(var_content);
	ft_free((void **)&before);
	if (!ft_streq(var_name, ""))
		ft_free((void **)&var_name);
	return (expanded_str);
}

static char	*ms_get_after_dollar(char *dollar)
{
	int		i;

	i = 0;
	if (ft_isdigit(dollar[i]))
		return (&dollar[i + 1]);
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
