/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:47:18 by liton             #+#    #+#             */
/*   Updated: 2017/08/25 02:47:43 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			command_setenv(char ***env, char *cmd, char *builtins)
{
	char	**new_env;
	char	**av;
	int		p;
	int		overwrite;

	(void)builtins;
	p = 0;
	av = ft_strsplit(cmd, ' ');
	new_env = NULL;
	if (av[3])
		overwrite = ft_atoi(av[3]);
	if (!*env || !av[1])
		return ;
	if ((p = search_v(*env, av[1])) == -1)
	{
		if (av[2])
			new_env = add_v(*env, av[1], av[2]);
		else
			new_env = add_v(*env, av[1], "");
		*env = new_env;
	}
	else if (av[2] && av[3] && overwrite != 0)
		modify_v(*env, p, av[1], av[2]);
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

void			command_unsetenv(char ***env, char *cmd, char *builtins)
{
	char	**new_env;
	char	**av;
	int		p;

	(void)builtins;
	p = 0;
	av = ft_strsplit(cmd, ' ');
	if (av[2])
	{
		ft_putendl_fd("unsetenv: too few arguments", 2);
		return ;
	}
	if (!*env || !av[1] || (p = search_v(*env, av[1])) == -1)
		return ;	
	new_env = del_v(*env, p);
	*env = new_env;
}

void			command_env(char **env, char *cmd, char *builtins)
{
	if (ft_strcmp(cmd, builtins) == 0)
		ft_display_tab(env);
}
