/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:14:53 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/30 13:18:47 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	ms_free_and_exit(char *str)
{
	free(str);
	exit(EXIT_FAILURE);
}
