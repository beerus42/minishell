/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 19:56:19 by liton             #+#    #+#             */
/*   Updated: 2017/08/01 02:39:51 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**strcpy_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	if (envp == NULL || *envp == NULL)
		return (NULL);
	while (envp[i])
		++i;
	if (!(env = (char**)malloc(sizeof(char*) * i) + 1))
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		if (!(env[i] = (char*)malloc(sizeof(char) * ft_strlen(envp[i]) + 1)))
			return (NULL);
		ft_strcpy(env[i], envp[i]);
	}
	env[i] = NULL;
	return (env);
}

int				main(int ac, char **av, char **envp)
{
	char		**env;
	char		*builtins;
	char		*cmd;

	(void)env;
	(void)av;
	if (ac != 1)
		return (0);
	env = strcpy_env(envp);
	while (42)
	{
		cmd = ft_strdup(read_cmd());
		builtins = ft_strdup(parsing(cmd));
		if (builtins == NULL)
		{
			command_not_found(cmd);
			continue ;
		}
		else
		{
			ft_builtins(env, cmd, builtins);
			free(cmd);
			free(builtins);
		}
	}
}
