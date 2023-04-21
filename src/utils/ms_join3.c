/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_join3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:29:02 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/21 05:08:18 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_join3(char *str1, char *str2, char *str3)
{
	char	*tmp1;
	char	*tmp2;
	char	*empty;

	empty = NULL;
	if (!str2)
		empty = "";
	if (empty)
	{
		tmp1 = ft_strjoin(str1, empty);
		if (!tmp1)
			return (NULL);
	}
	else
	{
		tmp1 = ft_strjoin(str1, str2);
		if (!tmp1)
			return (NULL);
	}
	tmp2 = ft_strjoin(tmp1, str3);
	if (!tmp2)
		return (ft_free((void **)&tmp1), NULL);
	ft_free((void **)&tmp1);
	return (tmp2);
}
