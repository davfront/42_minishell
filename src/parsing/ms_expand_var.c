/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:05:36 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/30 16:46:39 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **ms_get_all_var(char *str, char **var_array, char **env, int size);
static char	*ms_get_var_name(char *str, int i, int start);
static char	*ms_get_var_content(char *var_name, char **env);

static void printarr(char **cmd)
{
    for (int i = 0; cmd[i]; i++)
    {
        if (cmd[i])
            printf("[%d]=%s\n", i, cmd[i]);
    }
    printf("\n");
}

char    *ms_expand_var(char *str, char **env)
{
    int     size;
    char    **var_array;

    size = ms_count_var(str);
    var_array = malloc((size + 1) * sizeof(char *));
    if (!var_array)
        exit(EXIT_FAILURE);
    ms_get_all_var(str, var_array, env, size);
    printarr(var_array);
    return (NULL);
}

static char **ms_get_all_var(char *str, char **var_array, char **env, int size)
{
	int		i;
    int     j;
    char    *tmp;

	i = 0;
    j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			printf("$?\n");//ms_get_last_return_value();
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
	while (ft_isalpha(str[i]) == 1)
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

static char	*ms_get_var_content(char *var_name, char **env)
{
	int		i;
	int		len;
	int		content_len;
	char	*var_content;

	i = 0;
	len = ft_strlen(var_name);
    var_content = "";
	while (env[i] && (ft_strnstr(env[i], var_name, len) == 0))
		i++;
	if (env[i] != NULL && (ft_strnstr(env[i], var_name, len) != 0))
	{
		content_len = ms_content_len(len, env[i]);
		var_content = ft_substr(env[i], len, content_len);
	}
	return (var_content);
}


