/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 22:28:22 by liton             #+#    #+#             */
/*   Updated: 2017/09/06 19:48:29 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cd(char **av, char *path)
{
	free_env(av);
	ft_strdel(&path);
}

void	free_env(char **env)
{
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		ft_strdel(&env[i]);
		++i;
	}
	free(env);
	env = NULL;
}

void	command_echo(char *cmd)
{
	char	**av;
	int		i;

	i = 0;
	av = ft_split_whitespaces(cmd);
	while (av && av[++i])
	{
		ft_putstr(av[i]);
		if (av[i + 1])
			ft_putchar(' ');
	}
	ft_putchar('\n');
	free_env(av);
}

char	**strcpy_env(char **envp)
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

int		check_cmd(char *cmd)
{
	int		i;

	i = 0;
	while (cmd && cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		++i;
	if (cmd[i] == '\0')
		return (-1);
	return (0);
}
