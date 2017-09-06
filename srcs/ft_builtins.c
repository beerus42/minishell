/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 01:43:44 by liton             #+#    #+#             */
/*   Updated: 2017/09/06 23:32:18 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			command_exit(char *cmd)
{
	char	**av;

	av = ft_split_whitespaces(cmd);
	if (!av[1])
		exit(0);
	else
		exit(ft_atoi(av[1]));
}

static void			command_setenv(char ***env, char *cmd)
{
	char	**new_env;
	char	**av;
	int		p;

	p = 0;
	av = ft_split_whitespaces(cmd);
	new_env = NULL;
	if (support_setenv(*env, &av) == -1)
		return ;
	if ((p = search_v(*env, av[1])) == -1)
	{
		if (av[2])
			new_env = add_v(*env, av[1], av[2]);
		else
			new_env = add_v(*env, av[1], "");
		*env = new_env;
	}
	else if (av[2] && av[3] && ft_atoi(av[3]) != 0)
		modify_v(*env, p, av[1], av[2]);
	free_env(av);
}

static char			**del_v(char **env, int place)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new_env = (char**)malloc(sizeof(char*) * (size_env(env)))))
		return (NULL);
	while (env[i])
	{
		if (i == place)
			++i;
		if (env[i])
		{
			new_env[j] = ft_strdup(env[i]);
			++i;
			++j;
		}
	}
	free_env(env);
	new_env[j] = NULL;
	return (new_env);
}

static void			command_unsetenv(char ***env, char *cmd)
{
	char	**new_env;
	char	**av;
	int		p;

	p = 0;
	av = ft_split_whitespaces(cmd);
	if (!*env || !av[1] || (p = search_v(*env, av[1])) == -1)
	{
		free_env(av);
		return ;
	}
	if (av[2])
	{
		ft_putendl_fd("unsetenv: too few arguments", 2);
		free_env(av);
		return ;
	}
	new_env = del_v(*env, p);
	free_env(av);
	*env = new_env;
}

void				ft_builtins(char ***env, char *cmd, char *builtins)
{
	if (!ft_strcmp(builtins, "env"))
		command_env(*env, cmd, builtins);
	else if (!ft_strcmp(builtins, "cd"))
		binary_cd(env, cmd);
	else if (!(ft_strcmp(builtins, "unsetenv")))
		command_unsetenv(env, cmd);
	else if (!(ft_strcmp(builtins, "setenv")))
		command_setenv(env, cmd);
	else if (!(ft_strcmp(builtins, "exit")))
		command_exit(cmd);
	else if (!(ft_strcmp(builtins, "echo")))
		command_echo(cmd);
}
