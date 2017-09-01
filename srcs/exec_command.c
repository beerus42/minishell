/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 08:31:05 by liton             #+#    #+#             */
/*   Updated: 2017/09/01 23:09:19 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			error_exec(char *cmd)
{
	struct stat		buf;
	int				bol;

	bol = stat(cmd, &buf);
	if (bol == 0 && S_ISDIR(buf.st_mode))
		error_msg("bash: is a directory:", cmd);	
	else if (bol == 0 && !(buf.st_mode & S_IXUSR))
		error_msg("bash: persmission denied:", cmd);
	else if (bol == -1)
		error_msg("bash: no such file or directory", cmd);
}

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
	if (av[0] && av[0][0] != '.' && av[0][1] != '/')
		command_not_found(av[0]);
	else
		error_exec(av[0]);
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

	if ((i = search_v(*env, "PATH")) == -1 && cmd[0] != '/')
	{
		ft_putstr_fd("Variable PATH not set.\n", 2);
		return ;
	}
	pid = fork();
	if (pid > 0)
		wait(NULL);
	if (pid == 0)
	{
		av = ft_strsplit(cmd, ' ');
		if (execve(av[0], av, *env) == -1)
			support_exec_cmd(*env, pid, cmd, i);
		free_env(av);
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
