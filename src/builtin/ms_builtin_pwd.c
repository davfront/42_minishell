/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:37:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 18:24:16 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd failed");
		return (FAILURE);
	}
	printf("%s\n", cwd);
	return (SUCCESS);
}
