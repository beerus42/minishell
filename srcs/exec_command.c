/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 08:31:05 by liton             #+#    #+#             */
/*   Updated: 2017/09/06 20:23:34 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				error_exec(char *cmd)
{
	struct stat		buf;
	int				bol;

	bol = lstat(cmd, &buf);
	if (bol == 0 && S_ISDIR(buf.st_mode))
		error_msg("minishell: is a directory:", cmd);
	else if (bol == 0 && !(buf.st_mode & S_IXUSR))
		error_msg("minishell: persmission denied:", cmd);
	else if (bol == -1)
		error_msg("minishell: no such file or directory", cmd);
}

static void				search_binary(char **env_path, char **av, char **env)
{
	struct dirent		*dirent;
	DIR					*dir;
	char				*path;
	int					i;

	path = NULL;
	i = -1;
	while (env_path[++i])
	{
		dir = opendir(env_path[i]);
		while ((dirent = readdir(dir)))
		{
			if (!ft_strcmp(dirent->d_name, av[0]) && ft_strcmp(av[0], "."))
			{
				path = ft_strjoin(env_path[i], path);
				path = ft_strjoinfree(path, "/", 1);
				path = ft_strjoinfree(path, av[0], 1);
				closedir(dir);
				execve(path, av, env);
			}
		}
		closedir(dir);
	}
	ft_strdel(&path);
}

static void				support_exec_cmd(char **env, char *cmd, int i)
{
	char			**env_path;
	char			**av;

	av = ft_split_whitespaces(cmd);
	env_path = ft_strsplit(env[i] + 5, ':');
	search_binary(env_path, av, env);
	if (av[0] && ((av[0][0] != '.' && av[0][1] != '/')
		|| (av[0][0] == '.' && av[0][1] != '/')))
		command_not_found(av[0]);
	else
		error_exec(av[0]);
	free_env(av);
	free_env(env_path);
	exit(EXIT_FAILURE);
}

void					change_shlvl(char ***env)
{
	char	*shlvl;
	int		sh;
	char	**new;
	int		i;

	if ((i = search_v(*env, "SHLVL")) == -1)
	{
		new = add_v(*env, "SHLVL", "1");
		*env = new;
	}
	else
	{
		sh = ft_atoi((*env)[i] + 6);
		++sh;
		shlvl = ft_itoa(sh);
		modify_v(*env, i, "SHLVL", shlvl);
		ft_strdel(&shlvl);
	}
}

void					exec_command(char ***env, char *cmd)
{
	int			i;
	struct stat	buf;
	char		**av;
	pid_t		pid;

	pid = fork();
	if (pid > 0)
		wait(NULL);
	if (pid == 0)
	{
		av = ft_split_whitespaces(cmd);
		if (lstat(av[0], &buf) == 0
				&& (!(S_ISDIR(buf.st_mode)) && buf.st_mode & S_IXUSR))
		{
			split_exec_command(env, av[0]);
			execve(av[0], av, *env);
		}
		else if ((i = search_v(*env, "PATH")) == -1)
			ft_putstr_fd("Variable PATH not set.\n", 2);
		else
			support_exec_cmd(*env, cmd, i);
		free_env(av);
		exit(EXIT_FAILURE);
	}
}
