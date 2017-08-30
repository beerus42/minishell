/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:47:18 by liton             #+#    #+#             */
/*   Updated: 2017/08/30 22:15:30 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			command_exit(char *cmd)
{
	char	**av;

	av = ft_strsplit(cmd, ' ');
	if (!av[1])
		exit(0);
	else
		exit(ft_atoi(av[1]));
}

void			command_setenv(char ***env, char *cmd)
{
	char	**new_env;
	char	**av;
	int		p;

	p = 0;
	av = ft_strsplit(cmd, ' ');
	new_env = NULL;
	if (!*env || !av[1])
	{
		free_env(av);
		return ;
	}
	if ((p = search_v(*env, av[1])) == -1)
	{
		if (av[2])
			new_env = add_v(*env, av[1], av[2], 0);
		else
			new_env = add_v(*env, av[1], "", 0);
		*env = new_env;
	}
	else if (av[2] && av[3] && ft_atoi(av[3]) != 0)
		modify_v(*env, p, av[1], av[2]);
	free_env(av);
}

static char		**del_v(char **env, int place)
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
		if	(env[i])
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

void			command_unsetenv(char ***env, char *cmd)
{
	char	**new_env;
	char	**av;
	int		p;

	p = 0;
	av = ft_strsplit(cmd, ' ');
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

void			command_env(char **env, char *cmd, char *builtins)
{
	char	**new_env;
	char	*var;
	char	*val;
	int		i;
	char	**av;

	i = 0;
	new_env = NULL;
	if (ft_strcmp(cmd, builtins) == 0)
		ft_display_tab(env);
	else
	{
		av = ft_strsplit(cmd, ' ');
		while (av[1] && av[1][i] && av[1][i] != '=')
			++i;
		if (i == 0)
			ft_putendl_fd("Need variable.", 2);
		else if (!ft_strchr(av[1], '='))
			exec_command(&env, cmd);
		else if (ft_strcmp(ft_strchr(av[1], '='), ft_strrchr(av[1], '=')) != 0)
			ft_putendl_fd("Variable can not contain '='.", 2);
		else
		{
			var = ft_strsub(av[1], 0, i);
			val = ft_strsub(av[1], i + 1, ft_strlen(av[1]) - (i + 1));
			new_env = add_v(env, var, val, 1);
			exec_command(&new_env, cmd);
			free_env(new_env);
			ft_strdel(&var);
			ft_strdel(&val);
		}
		free_env(av);
	}
}
