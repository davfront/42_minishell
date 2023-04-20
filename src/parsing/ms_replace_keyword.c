/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_replace_keyword.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:02:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/12 15:34:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_replace_keyword(char **str, size_t kw_id, size_t kw_len, char *value)
{
	char	*before;
	char	*tmp1;
	char	*tmp2;

	before = ft_strndup(*str, kw_id);
	if (value)
	{
		tmp1 = ft_strjoin(before, value);
		ft_free((void **)&before);
	}
	else
		tmp1 = before;
	if (!tmp1)
		return (FAILURE);
	tmp2 = ft_strjoin(tmp1, *str + kw_id + kw_len);
	if (!tmp2)
	{
		ft_free((void **)&tmp1);
		return (FAILURE);
	}
	ft_free((void **)&tmp1);
	ft_free((void **)str);
	*str = tmp2;
	return (SUCCESS);
}
