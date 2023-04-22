/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_var_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:14:53 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/21 09:13:24 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_get_bracket_var_name(char *str, int index);
static int	ms_check_bracket(char *var_name);
static char	*ms_get_name(char *str, int index);

char	*ms_get_var_name(char *str, int index)
{
	char	*var_name;

	if (str[index] == '{')
	{
		var_name = ms_get_bracket_var_name(str, index);
		if (!var_name)
			return (ms_error3("bash", NULL, "bad substitution"), NULL);
		if (ms_check_bracket(var_name) == SUCCESS)
			return (var_name);
		else
		{
			ms_error3("bash", var_name, "bad substitution");
			ft_free((void **)&var_name);
			return (NULL);
		}
	}
	else
		var_name = ms_get_name(str, index);
	return (var_name);
}

static char	*ms_get_bracket_var_name(char *str, int index)
{
	int		start;
	int		end;
	char	*bracket_var_name;

	start = index;
	end = 0;
	if (ft_isdigit(str[index]))
		return (NULL);
	while (str[index] && str[index] != '}')
	{
		index++;
		end++;
	}
	bracket_var_name = ft_substr(str, start + 1, end - 1);
	return (bracket_var_name);
}

static int	ms_check_bracket(char *var_name)
{
	int		i;

	i = 0;
	if (ft_isdigit(var_name[i]))
		return (FAILURE);
	while (var_name[i])
	{
		if (var_name[i] != '_')
		{
			if (ft_strchr(" \t\n", var_name[i]) != NULL)
				return (FAILURE);
			if (ms_is_char_print(var_name[i]))
				return (FAILURE);
			if (ms_is_char_nprint(var_name[i]))
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static char	*ms_get_name(char *str, int index)
{
	int		start;
	int		end;
	char	*var_name;

	end = 0;
	start = index;
	if (ft_isdigit(str[index]))
	{
		var_name = "";
		return (var_name);
	}
	while (str[index] && (ft_isalnum(str[index]) || str[index] == '_'))
	{
		index++;
		end++;
	}
	var_name = ft_substr(str, start, end);
	return (var_name);
}
