/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 19:56:19 by liton             #+#    #+#             */
/*   Updated: 2017/08/21 05:51:54 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**strcpy_env(char **envp)
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

	
	if ((i = search_v(*env, "PATH")) == -1)
	{
		*env = add_v(*env, "PATH", "/Users/beerus/.rbenv/plugins/ruby-build/bin:/Users/beerus/.rbenv/shims:/Users/beerus/.rbenv/bin:/Users/beerus/.rvm/gems/ruby-2.4.1/bin:/Users/beerus/.rvm/gems/ruby-2.4.1@global/bin:/Users/beerus/.rvm/rubies/ruby-2.4.1/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Users/beerus/.rvm/bin");	
		i = size_env(*env) - 1;
	}
	pid = fork();
	if (pid > 0)
		wait(NULL);
	else
	{
		path = ft_strdup("/");
		av = ft_strsplit(cmd, ' ');
		env_path = ft_strsplit((*env)[i] + 5, ':');
		i = 0;
		while (env_path[i])
		{
			path = ft_strjoinfree(env_path[i], path, 1);
			path = ft_strjoinfree(path, av[0], 1);
			execve(path, av, *env);
			free(path);
			path = ft_strdup("/");
			++i;
		}
		command_not_found(av[0]);
		free(path);
	}
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
		cmd = ft_strdup(read_cmd());
		builtins = ft_strdup(parsing(cmd));
		if (builtins != NULL)
		{
			ft_builtins(&env, cmd, builtins);
			free(cmd);
			free(builtins);
		}
		else
			exec_command(&env, cmd);
	}
}
