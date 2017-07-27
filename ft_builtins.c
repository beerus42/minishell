/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:38:14 by liton             #+#    #+#             */
/*   Updated: 2017/07/27 23:06:42 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtins(char **cmd, char **env)
{
	if (!cmd || !cmd[0])
		return ;
	if (!ft_strcmp(cmd[0], "env"))
		command_env(cmd, env);	
	if (!ft_strcmp(cmd[0], "cd")
		command_cd(cd, env);
}
