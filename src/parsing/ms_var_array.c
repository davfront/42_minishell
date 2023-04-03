/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:05:36 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/03 15:54:13 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ms_get_all_var(char *str, char **var_array, \
		t_list *env, int size);
static char	*ms_get_var_name(char *str, int i, int start);
static char	*ms_get_var_content(char *var_name, t_list *env);
static char	*ms_content_from_list(char *var_name, t_list *head);

char	**ms_var_array(char *str, char **var_array, t_list *env)
{
	int		size;

	size = ms_count_var(str);
	var_array = malloc((size + 1) * sizeof(char *));
	if (!var_array)
		exit(EXIT_FAILURE);
	ms_get_all_var(str, var_array, env, size);
	return (var_array);
}

static char	**ms_get_all_var(char *str, char **var_array, t_list *env, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			var_array[j] = ms_get_exit_code(g_exit_code);
			j++;
		}
		else if (str[i] == '$' && !ms_is_quote(str[i + 1]))
		{
			tmp = ms_get_var_name(str, i + 1, i + 1);
			if (ms_get_var_content(tmp, env) != NULL)
				var_array[j] = ms_get_var_content(tmp, env);
			j++;
		}
		i++;
	}
	var_array[size] = '\0';
	return (var_array);
}

static char	*ms_get_var_name(char *str, int i, int start)
{
	int		end;
	char	*tmp;
	char	*var_name;

	end = 0;
	while (ft_isalpha(str[i]) == 1 || str[i] == '_')
	{
		i++;
		end++;
	}
	tmp = ft_substr(str, start, end);
	if (!tmp)
		return (NULL);
	var_name = ft_strjoin(tmp, "=");
	if (!var_name)
		ms_free_and_exit(tmp);
	free(tmp);
	return (var_name);
}

static char	*ms_get_var_content(char *var_name, t_list *env)
{
	t_list	*head;
	t_env	*tmp;
	char	*join;
	char	*var_content;

	head = env;
	while (head->next != NULL)
	{
		var_content = ms_content_from_list(var_name, head);
		if (ft_streq(var_content, "") == 0)
			return (var_content);
		head = head->next;
	}
	tmp = (t_env *)head->content;
	join = ft_strjoin(tmp->label, "=");
	if (!join)
		exit(EXIT_FAILURE);
	if (ft_streq(var_name, join) == 1)
	{
		var_content = ft_strdup(tmp->value);
		if (!var_content)
			exit(EXIT_FAILURE);
		return (free(join), var_content);
	}
	return (free(join), var_content);
}

static char	*ms_content_from_list(char *var_name, t_list *head)
{
	t_env	*tmp;
	char	*join;
	char	*var_content_tmp;

	tmp = (t_env *)head->content;
	join = ft_strjoin(tmp->label, "=");
	if (!join)
		exit(EXIT_FAILURE);
	if (ft_streq(var_name, join) == 1)
	{
		var_content_tmp = ft_strdup(tmp->value);
		if (!var_content_tmp)
			exit(EXIT_FAILURE);
		return (free(join), var_content_tmp);
	}
	var_content_tmp = "";
	return (free(join), var_content_tmp);
}
