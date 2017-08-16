/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_v.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:00:01 by liton             #+#    #+#             */
/*   Updated: 2017/08/16 00:50:43 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**del_v(char **env, int place)
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
