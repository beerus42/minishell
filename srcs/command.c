/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:47:18 by liton             #+#    #+#             */
/*   Updated: 2017/08/16 03:40:45 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_setenv(char ***env, char *cmd, char *builtins)
{
	char	**new_env;
	char	**av;
	int		p;

	(void)builtins;
	p = 0;
	av = ft_strsplit(cmd, ' ');
	new_env = NULL;
	if (!*env || !av[1])
		return ;
		if (search_v(*env, av[1], &p))
	{
		if (av[2])
			new_env = add_v(*env, av[1], av[2]);
		else
			new_env = add_v(*env, av[1], "");
		*env = new_env;
	}
	else if (av[2] && av[3] && ft_strcmp(av[3], "0"))
		modify_v(*env, p, av[1], av[2]);
}

void	command_unsetenv(char ***env, char *cmd, char *builtins)
{
	char	**new_env;
	char	**av;
	int		p;

	(void)builtins;
	p = 0;
	av = ft_strsplit(cmd, ' ');
	if (!*env || !av[1] || search_v(*env, av[1], &p))
		return ;
	new_env = del_v(*env, p);
	*env = new_env;
}

void		command_env(char **env, char *cmd, char *builtins)
{
	if (ft_strcmp(cmd, builtins) == 0)
		ft_display_tab(env);
}

void		command_ls(char **env, char *cmd, char *builtins)
{
	pid_t	pid;
	char	**av;

	pid = fork();
	(void)builtins;
	if (pid > 0)
		wait(NULL);
	else
	{
		av = ft_strsplit(cmd, ' ');
		execve("/bin/ls", av, env);
	}
}
