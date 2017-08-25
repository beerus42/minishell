/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 23:43:56 by liton             #+#    #+#             */
/*   Updated: 2017/08/25 00:51:37 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		support_cd(char **av)
{
	int		nb_av;

	nb_av = 0;
	while(av[nb_av])
		++nb_av;
	if (nb_av > 2)
	{
		error_msg("cd: too few arguments", NULL);
		return (-1);
	}
	return (0);
}

static void		modify_env(char ***env, char *dir)
{
	int		p;
	char	**new_env;

	if ((p = search_v(*env, "OLDPWD")) != -1)
		modify_v(*env, p, "OLDPWD", dir);
	else
	{
		new_env = add_v(*env, "OLDPWD", dir);
		*env = new_env;
	}
	if ((p = search_v(*env, "PWD")) != -1)
		modify_v(*env, p, "PWD", getcwd(dir, 100));
	else
	{
		new_env = add_v(*env, "PWD", getcwd(dir, 100));
		*env = new_env;
	}
}

void			binary_cd(char ***env, char *cmd)
{
	int		p;
	char	**av;
	char	*dir;
	char	*path;

	dir = NULL;
	av = ft_strsplit(cmd, ' ');
	dir = getcwd(dir, 100);
	path = ft_strnew(0);
	if (support_cd(av) == -1)
		return ;
	if (!ft_strcmp(av[1], "-"))
	{
		if ((p = search_v(*env, "OLDPWD")) == -1)
		{
			ft_putstr_fd("Variable OLDPWD not set.\n", 2);
			return ;
		}
		path = ft_strjoinfree(path, (*env)[p] + 7, 1);
		ft_putendl(path);
	}
	else if (av[1] && av[1][0] != '/')
	{
		free(path);
		path = ft_strdup("/");
		path = ft_strjoinfree(dir, path, 2);
		path = ft_strjoinfree(path, av[1], 1);
	}
	else if (av[1][0] == '/')
		path = ft_strjoinfree(path, av[1], 1);
	if (chdir(path))
	{
		error_msg("cd: no such file or directory", av[1]);
		return ;
	}
	modify_env(env, dir);
}
