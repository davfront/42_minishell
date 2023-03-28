/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:24:13 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/28 17:39:50 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_count_rows(char *str, char *set);
static char	**ms_str(char **arr, char *str, char *set, t_trim *trim);
static void	ms_init_struct_trim(char *str, t_trim *trim);

char	**ms_cmdtrim(char *str, char *set)
{
	t_trim	trim;
	char	**array;
	int		count;

	if (!str)
		return (NULL);
	count = ms_count_rows(str, set);
	array = malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = ms_str(array, str, set, &trim);
	if (!array)
		exit(EXIT_FAILURE);
	array[count] = '\0';
	return (array);
}

static char	**ms_str(char **arr, char *str, char *set, t_trim *trim)
{
	ms_init_struct_trim(str, trim);
	while (str[trim->i] != '\0')
	{
		while (ft_strchr(set, str[trim->i]) && str[trim->i] != '\0')
			trim->i++;
		trim->j = trim->i;
		while (str[trim->i] != '\0')
		{
			if ((str[trim->i] == '\"' || str[trim->i] == '\'') && !trim->quotes)
				trim->quotes = str[trim->i];
			else if (str[trim->i] == trim->quotes)
				trim->quotes = 0;
			else if (ft_strchr(set, str[trim->i]) && !trim->quotes)
				break ;
			trim->i++;
		}
		if (trim->j >= trim->len)
			arr[trim->k++] = "\0";
		else
			arr[trim->k++] = ft_substr(str, trim->j, trim->i - trim->j);
	}
	return (arr);
}

static int	ms_count_rows(char *str, char *set)
{
	int	count;
	int	quotes;

	count = 0;
	quotes = 0;
	while (*str)
	{
		if (!ft_strchr(set, *str))
		{
			count++;
			while ((!ft_strchr(set, *str) || quotes) && *str)
			{
				if (!quotes && (*str == '\"' || *str == '\''))
					quotes = *str;
				else if (quotes == *str)
					quotes = 0;
				str++;
			}
		}
		else
			str++;
	}
	return (count);
}

static void	ms_init_struct_trim(char *str, t_trim *trim)
{
	trim->i = 0;
	trim->j = 0;
	trim->k = 0;
	trim->quotes = 0;
	trim->len = ft_strlen(str);
}
