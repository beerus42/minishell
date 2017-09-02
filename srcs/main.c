/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 19:56:19 by liton             #+#    #+#             */
/*   Updated: 2017/09/02 20:31:53 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			check_cmd(char *cmd)
{
	int		i;

	i = 0;
	while (cmd && cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		++i;
	if (cmd[i] == '\0')
		return (-1);
	return (0);
}

static char			*parsing(char *cmd)
{
	int						i;
	int						end;
	int						k;
	char					*builtins;
	static const char		*b[6] = {"env", "cd", "echo", "unsetenv",
		"setenv", "exit"};

	i = -1;
	end = 0;
	if (!cmd[0] || !cmd[1])
		return (0);
	while (cmd[end] && cmd[end] == ' ')
		++end;
	k = end;
	while (cmd[end + 1] && cmd[end + 1] != ' ')
		++end;
	builtins = ft_strsub(cmd, k, (end - k) + 1);
	while (++i < 6)
	{
		if (!ft_strcmp(builtins, b[i]))
			return (builtins);
	}
	ft_strdel(&builtins);
	return (NULL);
}

static char			**strcpy_env(char **envp)
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

static char			*read_cmd(void)
{
	char	buf[5 + 1];
	char	*save;
	int		ret;
	int		quit;

	quit = 1;
	save = ft_strnew(0);
	ft_putstr_fd("$> ", 0);
	while (quit && (ret = read(0, buf, 5)) > 0)
	{
		buf[ret] = '\0';
		if (ft_strchr(buf, '\n'))
		{
			buf[ret - 1] = '\0';
			quit = 0;
		}
		save = ft_strjoinfree(save, buf, 1);
	}
	return (save);
}

int					main(int ac, char **av, char **envp)
{
	char		**env;
	char		*builtins;
	char		*cmd;

	(void)av;
	if (ac != 1)
		return (0);
	env = strcpy_env(envp);
	while (42)
	{
		cmd = read_cmd();
		builtins = parsing(cmd);
		if (builtins != NULL)
		{
			ft_builtins(&env, cmd, builtins);
			ft_strdel(&cmd);
			ft_strdel(&builtins);
		}
		else if (cmd && check_cmd(cmd) != -1)
		{
			exec_command(&env, cmd);
			ft_strdel(&cmd);
		}
	}
}
