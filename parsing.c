/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 16:45:17 by liton             #+#    #+#             */
/*   Updated: 2017/07/27 21:48:35 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parsing(char *cmd, char ***cmd_split)
{
	static const char		*b[6] = {"env", "cd", 
									"echo", "unsetenv", 
									"setenv", "exit"};
	int						i;
	int		j;

	j = 0;
	if (!cmd[0])
		return (0);
	*cmd_split = ft_strsplit(cmd, ' ');
	i = -1;
	while (++i < 6)
	{
		if (ft_strcmp((*cmd_split)[0], b[i]) == 0)
			return (1);
	}
	return (0);
}
