/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:38:14 by liton             #+#    #+#             */
/*   Updated: 2017/08/01 23:59:09 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtins(char **env, char *cmd, char *builtins)
{
	if (!ft_strcmp(builtins, "env"))
		command_env(env, cmd, builtins);	
	if (!ft_strcmp(builtins, "cd"))
		binary_cd(env, cmd);
	if (!ft_strcmp(builtins, "ls"))
		command_ls(env, cmd, builtins);
}
