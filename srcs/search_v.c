/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 23:19:37 by liton             #+#    #+#             */
/*   Updated: 2017/09/01 04:16:12 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_v(char **env, char *str)
{
	int		i;
	int		j;
	int		k;
	int		save;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (-1);
	while (str && str[i + 1])
		++i;
	save = i;
	while (env[j])
	{
		k = 0;
		i = save;
		while (env[j][k + 1] != '=')
			++k;
		while (env[j][k] == str[i])
		{
			if (k == 0 && i == 0)
				return (j);
			--k;
			--i;
		}
		++j;
	}
	return (-1);
}
