/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osterger <osterger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:29:02 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/05 23:22:49 by osterger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ms_join(char *str1, char *str2, char *str3)
{
	char	*tmp1;
	char	*tmp2;

	if (!str1)
		str1 = "";
    if (!str2)
		str2 = "";
    if (!str3)
		str3 = "";
	tmp1 = ft_strjoin(str1, str2);
	if (!tmp1)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, str3);
	if (!tmp2)
		return (ft_free((void **)&tmp1), NULL);
	ft_free((void **)&tmp1);
	return (tmp2);
}