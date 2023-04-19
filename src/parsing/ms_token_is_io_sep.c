/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_is_io_sep.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:40:24 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 12:16:22 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_token_is_io_sep(char *token)
{
	if (ft_streq(token, "<"))
		return (1);
	if (ft_streq(token, "<<"))
		return (1);
	if (ft_streq(token, ">"))
		return (1);
	if (ft_streq(token, ">>"))
		return (1);
	return (0);
}
