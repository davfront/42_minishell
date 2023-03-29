/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:43:18 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/29 11:04:31 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_parser(char *str)
{
	char	**cmds;

	cmds = ms_cmdsplit(str, " ");
	if (!cmds)
		exit(EXIT_FAILURE);
	return (cmds);
}
