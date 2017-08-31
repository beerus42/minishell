/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 08:31:05 by liton             #+#    #+#             */
/*   Updated: 2017/08/31 18:16:14 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			support_exec_cmd(char **env, pid_t pid, char *cmd, int i)
{
	char	**env_path;
	char	**av;
	char	*path;

	av = ft_strsplit(cmd, ' ');
	env_path = ft_strsplit(env[i] + 5, ':');
	path = NULL;
	i = -1;
	while (env_path[++i])
	{
		path = ft_strjoin(env_path[i], path);
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoinfree(path, av[0], 1);
		execve(path, av, env);
		ft_strdel(&path);
	}
	command_not_found(av[0]);
	ft_strdel(&path);
	free_env(av);
	free_env(env_path);
	exit(pid);
}

void				exec_command(char ***env, char *cmd)
{
	int			i;
	char		**av;
	pid_t		pid;

	if ((i = search_v(*env, "PATH")) == -1)
	{
		ft_putstr_fd("Variable PATH not set.\n", 2);
		return ;
	}
	pid = fork();
	if (pid > 0)
		wait(NULL);
	if (pid == 0 && cmd[0] != '/')
		support_exec_cmd(*env, pid, cmd, i);
	else if (pid == 0 && cmd[0] == '/')
	{
		av = ft_strsplit(cmd, ' ');
		execve(av[0], av, *env);
		command_not_found(av[0]);
		free_env(av);
		exit(pid);
	}
}

void				command_echo(char *cmd)
{
	char	**av;
	int		i;

	i = 0;
	av = ft_strsplit(cmd, ' ');
	while (av[++i])
	{
		ft_putstr(av[i]);
		if (av[i + 1])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}
