/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 23:43:56 by liton             #+#    #+#             */
/*   Updated: 2017/08/02 02:40:50 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		support(char **env, char *av, int pwd, int oldpwd)
{	
	char	*path;

	free(env[oldpwd]);
	if (av[0] == '/')
	{
		path = ft_strdup("/");
		env[oldpwd] = ft_strdup(env[pwd] + 4);
	}
	else
	{
		path = ft_strnew(0);
		path = ft_strjoin(path, env[pwd] + 4);
		env[oldpwd] = ft_strdup(path);
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoin(path, av);
	}
	env[oldpwd] = ft_strjoinfree("OLDPWD=", env[oldpwd], 2);
	chdir(path);
	free(env[pwd]);
	env[pwd] = ft_strdup(getcwd(env[pwd], 100));
	env[pwd] = ft_strjoinfree("PWD=", env[pwd], 2);
	free(path);
}

void			binary_cd(char **env, char *cmd)
{
	int		home;
	int		pwd;
	int		oldpwd;
	int		i;
	char	**av;

	i = 0;
	av = ft_strsplit(cmd + 2, ' ');
	while (av && av[i] && av[i][0] == '-')
		++i;
	pwd = search_v(env, "PWD");
	oldpwd = search_v(env, "OLDPWD");
	if (av[i] && av[i][0] != '~')
		support(env, av[i], pwd, oldpwd);
	else
	{
		free(env[oldpwd]);
		env[oldpwd] = ft_strdup(env[pwd] + 4);
		env[oldpwd] = ft_strjoinfree("OLDPWD=", env[oldpwd], 2);
		free(env[pwd]);
		home = search_v(env, "HOME");
		env[pwd] = ft_strdup(env[home] + 5);
		env[pwd] = ft_strjoinfree("PWD=", env[pwd], 2);	
		chdir(env[home] + 5);
	}
}
