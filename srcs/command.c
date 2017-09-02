/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:47:18 by liton             #+#    #+#             */
/*   Updated: 2017/09/02 17:27:56 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			command_env(char **env, char *cmd, char *builtins)
{
	char	**new_env;
//	char	*var;
//	char	*val;
	int		i;
	char	**av;

	i = 0;
	new_env = NULL;
	if (ft_strcmp(cmd, builtins) == 0)
		ft_display_tab(env);
	else
	{
		av = ft_strsplit(cmd, ' ');
		while (av[1] && av[1][i] && av[1][i] != '=')
			++i;
		if (i == 0)
			ft_putendl_fd("Need variable.", 2);
		else if (!ft_strchr(av[1], '='))
			exec_command(&env, cmd);
		else if (ft_strcmp(ft_strchr(av[1], '='), ft_strrchr(av[1], '=')) != 0)
			ft_putendl_fd("Variable can not contain '='.", 2);
		else
		{
//			var = ft_strsub(av[1], 0, i);
//			val = ft_strsub(av[1], i + 1, ft_strlen(av[1]) - (i + 1));
//			if (i == serch_v(env,
		//	new_env = add_v(env, var, val, 1);
			exec_command(&env, cmd);
			//free_env(new_env);
	//		ft_strdel(&var);
	//		ft_strdel(&val);
		}
//		free_env(av);
	}
}
