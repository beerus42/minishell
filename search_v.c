/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 23:19:37 by liton             #+#    #+#             */
/*   Updated: 2017/08/02 01:11:14 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_v(char **env, char *str)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		 while (env[i] && env[i][0] != str[0])
			++i;
		if (ft_strstr(env[i], str))
			return (i);
	}
	return (-1);
}
