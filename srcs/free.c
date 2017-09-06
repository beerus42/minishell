/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 22:28:22 by liton             #+#    #+#             */
/*   Updated: 2017/09/06 04:36:04 by liton            ###   ########.fr       */
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
