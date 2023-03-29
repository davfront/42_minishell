/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:43:18 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/29 10:33:59 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parser(char *str)
{
	char	**cmds;

	cmds = ms_cmdtrim(str, " ");
	if (!cmds)
		return (-1);
	ft_free_split(cmds);
	return (0);
}
