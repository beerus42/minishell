/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 19:56:19 by liton             #+#    #+#             */
/*   Updated: 2017/07/27 22:52:13 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	char		**cmd_split;
	char		*cmd;

	(void)av;
	cmd_split = NULL;
	if (ac != 1)
		return (0);
	while (42)
	{
		cmd = ft_strdup(read_cmd());
		if (cmd_split)
			ft_strclr(cmd_split[0]);
		if (!(parsing(cmd, &cmd_split)) && cmd_split)
		{
			
			command_not_found(cmd_split[0]);
			continue ;
		}
		ft_builtins(cmd_split, env);
	}
}
