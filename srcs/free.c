/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 22:28:22 by liton             #+#    #+#             */
/*   Updated: 2017/08/31 17:00:31 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cd(char **av, char *dir, char *path, int bol)
{
	if (bol == 0)
		ft_strdel(&dir);
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

void	free_string(char **str)
{
	free(*str);
	*str = NULL;
}
