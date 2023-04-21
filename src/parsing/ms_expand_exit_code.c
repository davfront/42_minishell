/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_exit_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:53:15 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/21 09:01:31 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_expand_exit_code(char *copy_str, int *index)
{
	int		i;
	char	*before;
	char	*after;
	char	*exit_code_as_str;
	char	*expand_str;

	i = *index;
	before = ft_substr(copy_str, 0, i);
	if (!before)
		return (NULL);
	after = &copy_str[i + 2];
	exit_code_as_str = ft_itoa(g_exit_code);
	if (!exit_code_as_str)
		return (ft_free((void **)&before), NULL);
	expand_str = ms_join3(before, exit_code_as_str, after);
	if (!expand_str)
	{
		ft_free((void **)&before);
		ft_free((void **)&exit_code_as_str);
		return (NULL);
	}
	(*index) += ft_strlen(exit_code_as_str);
	ft_free((void **)&before);
	ft_free((void **)&exit_code_as_str);
	return (expand_str);
}
