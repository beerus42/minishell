/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:47:18 by liton             #+#    #+#             */
/*   Updated: 2017/07/28 18:19:07 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		command_env(char **env, char *cmd, char *builtins)
{
	if (ft_strcmp(cmd, builtins) == 0)
		ft_display_tab(env);
}

void		command_cd(char **env, char *cmd, char *builtins)
{
	char	**av;

	(void)builtins;
	av = ft_strsplit(cmd + 2, ' ');
	execve("/bin/cd", av, env);	
}

void	command_ls(char **env, char *cmd, char *builtins)
{
	char	**av;

	(void)builtins;
	(void)env;
	av = ft_strsplit(cmd + 2, ' ');
	execve("/bin/ls", av, NULL);
}
