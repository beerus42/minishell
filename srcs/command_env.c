/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:47:18 by liton             #+#    #+#             */
/*   Updated: 2017/09/06 17:16:59 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			new_variable(char ***env, char **av, int *i)
{
	char	*var;
	char	*val;
	int		j;
	int		p;

	while (av[++(*i)] && ft_strchr(av[*i], '='))
	{
		if (av[*i][0] != '=')
		{
			j = 0;
			while (av[*i][j + 1] != '=')
				++j;
			var = ft_strsub(av[*i], 0, j + 1);
			val = ft_strdup(av[*i] + (j + 2));
			if ((p = search_v(*env, var)) == -1)
				*env = add_v(*env, var, val);
			else
				modify_v(*env, p, var, val);
			ft_strdel(&var);
			ft_strdel(&val);
		}
	}
}

static void			exec_env(char **av, char **new_cmd, int i, char **new_env)
{
	if (av[i])
	{
		while (av[i])
		{
			*new_cmd = ft_strjoinfree(*new_cmd, av[i++], 1);
			*new_cmd = ft_strjoinfree(*new_cmd, " ", 1);
		}
		exec_command(&new_env, *new_cmd);
	}
	else
		ft_display_tab(new_env);
}

void				command_env(char **env, char *cmd, char *builtins)
{
	int		i;
	char	**new_env;
	char	**av;
	char	*new_cmd;

	new_env = NULL;
	new_cmd = ft_strnew(0);
	i = 0;
	if (ft_strcmp(cmd, builtins) == 0)
		ft_display_tab(env);
	else
	{
		av = ft_split_whitespaces(cmd);
		new_env = strcpy_env(env);
		new_variable(&new_env, av, &i);
		exec_env(av, &new_cmd, i, new_env);
		free_env(av);
		free_env(new_env);
	}
	ft_strdel(&new_cmd);
}
