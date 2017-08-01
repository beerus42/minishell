/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 16:45:17 by liton             #+#    #+#             */
/*   Updated: 2017/08/01 02:22:28 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char		*parsing(char *cmd)
{
	int						i;
	int						j;
	int						end;
	static const char		*b[7] = {"env", "cd", "echo", "unsetenv", 
									  "setenv", "exit", "ls"};

	i = 0;
	end = 0;
	if (!cmd[0] || !cmd[1])
		return (0);
	while (cmd[end + 1] && cmd[end + 1] != ' ')
		++end;
	while (i < 7)
	{
		j = 0;
		while (cmd[j] == b[i][j] && j <= end)
			++j;
		if (j == end + 1 && b[i][j] == '\0')
			return (b[i]);
		++i;
	}
	return (NULL);
}