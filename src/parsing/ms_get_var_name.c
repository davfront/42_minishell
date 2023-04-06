/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_var_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osterger <osterger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:14:53 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/06 01:45:32 by osterger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_is_bracket(char *str, int index);
static int	ms_check_bracket(char *var_name);
static char	*ms_get_name(char *str, int index);

char	*ms_get_var_name(char *str, int index)
{
	char	*var_name;
	
	if (str[index] == '{')
	{
		var_name = ms_is_bracket(str, index);
		if (ms_check_bracket(var_name) == SUCCESS)
			return (var_name);
		else
		{
			ms_error3("bash", var_name, "bad substitution");
			return (NULL);
		}
	}
	else
		var_name = ms_get_name(str, index);
	return (var_name);
}

static char	*ms_is_bracket(char *str, int index)
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
	if (!bracket_var_name)
		return (NULL);
	return (bracket_var_name);
}

static int	ms_check_bracket(char *var_name)
{
	int		i;

	i = 0;
	while (var_name[i])
	{
		if (ft_strchr(" \t\n", var_name[i]) != NULL)
			return (FAILURE);
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
	if (str[index] == '{')
		index++;
	start = index;
	if (ft_isdigit(str[index]))
		return (NULL);
	while (str[index] != '}' && (ft_isalnum(str[index]) || str[index] == '_'))
	{
		index++;
		end++;
	}
	var_name = ft_substr(str, start, end);
	if (!var_name)
		return (NULL);
	return (var_name);
}