/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 19:56:19 by liton             #+#    #+#             */
/*   Updated: 2017/08/26 01:08:57 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char		*parsing(char *cmd)
{
	int						i;
	int						j;
	int						end;
	static const char		*b[6] = {"env", "cd", "echo", "unsetenv",
									  "setenv", "exit"};

	i = 0;
	end = 0;
	if (!cmd[0] || !cmd[1])
		return (0);
	while (cmd[end + 1] && cmd[end + 1] != ' ')
		++end;
	while (i < 6)
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

static char		**strcpy_env(char **envp)
{
	char	**env;
	int		i;

	if (envp == NULL || *envp == NULL)
		return (NULL);
	if (!(env = (char**)malloc(sizeof(char*) * (size_env(envp) + 1))))
		return (NULL);
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

void			exec_command(char ***env, char *cmd)
{
	char		**av;
	int			i;
	pid_t		pid;
	char		**env_path;
	char		*path;

	path = NULL;
	if ((i = search_v(*env, "PATH")) == -1)
	{
		ft_putstr_fd("Variable PATH not set.\n", 2);
		return ;
	}
	pid = fork();
	if (pid > 0)
		wait(NULL);
	else
	{
		av = ft_strsplit(cmd, ' ');
		env_path = ft_strsplit((*env)[i] + 5, ':');
		i = 0;
		while (env_path[i])
		{
			path = ft_strjoin(env_path[i], path);
			path = ft_strjoinfree(path, "/", 1);
			path = ft_strjoinfree(path, av[0], 1);
			execve(path, av, *env);
			ft_strdel(&path);
			++i;
		}
		command_not_found(av[0]);
		ft_strdel(&path);
		free_env(av);
		free_env(env_path);
		exit(pid);
	}
}

char		*read_cmd(void)
{
	char	buf[5 + 1];
	char	*save;
	int		ret;
	int		quit;

	quit = 1;
	save = ft_strnew(0);
	ft_putstr_fd("$> ", 0);
	while (quit && (ret = read(0, buf, 5)) > 0)
	{
		buf[ret] = '\0';
		if (ft_strchr(buf, '\n'))
		{
			buf[ret - 1] = '\0';
			quit = 0;
		}
		save = ft_strjoinfree(save, buf, 1);
	}
	return (save);
}

int				main(int ac, char **av, char **envp)
{
	char		**env;
	char		*builtins;
	char		*cmd;

	(void)av;
	if (ac != 1)
		return (0);
	env = strcpy_env(envp);
	while (42)
	{
		cmd = read_cmd();
		builtins = ft_strdup(parsing(cmd));
		if (builtins != NULL)
		{
			ft_builtins(&env, cmd, builtins);
			ft_strdel(&cmd);
			ft_strdel(&builtins);
		}
		else if (cmd)
		{
			exec_command(&env, cmd);
			ft_strdel(&cmd);	
		}
	}
}
