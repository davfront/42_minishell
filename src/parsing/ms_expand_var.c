/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:58:58 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/11 17:31:28 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_change_line(char *str, char **var_array, int i, int j);
static char	*ms_get_before_dollar(char *tmp, int i);
static char	*ms_get_after_dollar(char *tmp, int i);
static char	*ms_join(char *before, char *after, char *var_array);

char	*ms_expand_var(char *str, t_list *env)
{
	char	**var_array;
	char	*res;

	var_array = NULL;
	var_array = ms_var_array(str, var_array, env);
	if (!var_array)
		return (NULL);
	res = ms_change_line(str, var_array, 0, 0);
	if (!res)
		return (NULL);
	res = ms_tilde(res, env);
	if (!res)
		return (NULL);
	ms_free_array(var_array);
	return (res);
}

static char	*ms_change_line(char *s, char **var_array, int i, int j)
{
	char	*before;
	char	*after;
	char	*str;
	char	*new_str;

	str = ft_strdup(s);
	while (str[i])
	{
		if (str[i] == '$' && !ms_char_print(str[i + 1]))
		{
			before = ms_get_before_dollar(str, i - 1);
			after = NULL;
			if (str[i + 1] == '?')
				after = &str[i + 2];
			else if (ft_isalnum(str[i + 1]) || ms_char_nprint(str[i + 1]))
				after = ms_get_after_dollar(str, i + 1);
			if (after)
			{
				new_str = ms_join(before, after, var_array[j]);
				i += ft_strlen(var_array[j]) - 1;
				ft_free((void **)&str);
				str = new_str;
			}
			ft_free((void **)&before);
			j++;
		}
		i++;
	}
	return (str);
}

static char	*ms_get_before_dollar(char *tmp, int i)
{
	char	*res;

	res = ft_substr(tmp, 0, i + 1);
	if (!res)
		return (NULL);
	return (res);
}

static char	*ms_get_after_dollar(char *tmp, int i)
{
	if (ms_char_nprint(tmp[i]))
	{
		while (tmp[i] && ms_char_nprint(tmp[i]))
			i++;
		return (&tmp[i]);
	}
	while (tmp[i] && (ft_isalnum(tmp[i]) || tmp[i] == '_'))
		i++;
	return (&tmp[i]);
}

static char	*ms_join(char *before, char *after, char *var_array)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(before, var_array);
	if (!tmp1)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, after);
	if (!tmp2)
		return (ft_free((void **)&tmp1), NULL);
	ft_free((void **)&tmp1);
	return (tmp2);
}
