/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:58:58 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/04 17:37:27 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_change_line(char *str, char **var_array, int i, int j);
static char	*ms_get_before_dollar(char *tmp, int i);
static char	*ms_get_after_dollar(char *tmp, int i);
static char	*ms_join(char *before, char *after, char **var_array, int j);

char	*ms_expand_var(char *str, t_list *env)
{
	char	**var_array;
	char	*res;

	var_array = NULL;
	var_array = ms_var_array(str, var_array, env);
	if (!var_array)
		exit (EXIT_FAILURE);
	res = ms_change_line(str, var_array, 0, 0);
	if (!res)
		exit(EXIT_FAILURE);
	res = ms_tilde(res, env);
	if (!res)
		exit(EXIT_FAILURE);
	ms_free_array(var_array);
	return (res);
}

static char	*ms_change_line(char *str, char **var_array, int i, int j)
{
	char	*tmp;
	char	*before;
	char	*after;

	tmp = ft_strdup(str);
	if (!tmp)
		exit(EXIT_FAILURE);
	while (tmp[i])
	{
		if (tmp[i] == '$' && !ms_char_print(tmp[i + 1]))
		{
			before = ms_get_before_dollar(tmp, i - 1);
			if (tmp[i + 1] == '?')
				after = &tmp[i + 2];
			else if (ft_isalnum(tmp[i + 1]))
				after = ms_get_after_dollar(tmp, i + 1);
			else if (ms_char_nprint(tmp[i + 1]))
				after = "";
			tmp = ms_join(before, after, var_array, j);
			j++;
		}
		i++;
	}
	return (tmp);
}

static char	*ms_get_before_dollar(char *tmp, int i)
{
	char	*res;

	res = ft_substr(tmp, 0, i + 1);
	if (!res)
		exit(EXIT_FAILURE);
	return (res);
}

static char	*ms_get_after_dollar(char *tmp, int i)
{
	while (tmp[i] && (ft_isalnum(tmp[i]) || tmp[i] == '_'))
		i++;
	return (&tmp[i]);
}

static char	*ms_join(char *before, char *after, char **var_array, int j)
{
	char	*tmp;

	tmp = ft_strdup(before);
	if (!tmp)
		exit(EXIT_FAILURE);
	tmp = ft_strjoin(tmp, var_array[j]);
	if (!tmp)
		exit(EXIT_FAILURE);
	tmp = ft_strjoin(tmp, after);
	if (!tmp)
		exit(EXIT_FAILURE);
	free(before);
	return (tmp);
}
