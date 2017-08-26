/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 23:43:56 by liton             #+#    #+#             */
/*   Updated: 2017/08/26 04:23:00 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_cd(char **av, char *dir, char *path, int bol)
{
	if (bol == 0)
		ft_strdel(&dir);
	free_env(av);
	ft_strdel(&path);
}

static int		support_cd(char **av, char *dir, char **env, char **path)
{
	int		nb_av;
	int		p;

	nb_av = 0;
	p = 0;
	while(av[nb_av])
		++nb_av;
	if (nb_av > 2)
	{
		error_msg("cd: too few arguments", NULL);
		free_cd(av, dir, *path, 0);
		return (-1);
	}
	if (!av[1])
	{
		if ((p = search_v(env, "HOME")) == -1)
		{
			ft_putstr_fd("Variable HOME not set.\n", 2);
			free_cd(av, dir, *path, 0);
			return (-1);
		}
		*path = ft_strjoinfree(*path, env[p] + 5, 1);
	}
	return (0);
}

static int	support_cd_2(char **av, char *dir, char **env, char **path)
{
	int		p;

	if (!ft_strcmp(av[1], "-"))
	{
		if ((p = search_v(env, "OLDPWD")) == -1)
		{
			ft_putstr_fd("Variable OLDPWD not set.\n", 2);
			free_cd(av, dir, *path, 0);
			return (-1);
		}
		*path = ft_strjoinfree(*path, env[p] + 7, 1);
		ft_putendl(*path);
	}
	else if (av[1] && av[1][0] != '/')
	{
		ft_strdel(path);
		*path = ft_strdup("/");
		*path = ft_strjoinfree(dir, *path, 2);
		*path = ft_strjoinfree(*path, av[1], 1);
	}
	else if (av[1][0] == '/')
		*path = ft_strjoinfree(*path, av[1], 1);
	return (0);
}

static void		modify_env(char ***env, char *dir)
{
	int		p;
	char	**new_env;

	new_env = NULL;
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
	char	**av;
	char	*dir;
	char	*path;

	dir = NULL;
	av = ft_strsplit(cmd, ' ');
	dir = getcwd(dir, 100);
	path = ft_strnew(0);
	if ((support_cd(av, dir, *env, &path)) == -1)
		return ;
	 else if (!path[0] && (support_cd_2(av, dir, *env, &path)) == -1)
		return ;
	if (chdir(path))
	{
		if (access(path, X_OK) == -1)
			error_msg("cd: permission denied:", av[1]);
		else
			error_msg("cd: no such file or directory", av[1]);
		free_cd(av, dir, path, 0);
		return ;
	}
	free_cd(av, dir, path, 1);
	modify_env(env, dir);
	ft_strdel(&dir);
}
