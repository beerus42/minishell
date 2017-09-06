/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 19:56:19 by liton             #+#    #+#             */
/*   Updated: 2017/09/06 20:23:05 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char				*parsing(char *cmd)
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
	while (cmd[end] && (cmd[end] == ' ' || cmd[end] == '\t'))
		++end;
	k = end;
	while (cmd[end + 1] && (cmd[end + 1] != ' ' && cmd[end + 1] != '\t'))
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

static char				*read_cmd(void)
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
	if (ret == 0)
		ft_putchar('\n');
	return (save);
}

static void				env_null(char ***env)
{
	if (!(*env = (char**)malloc(sizeof(char*) * 5)))
		return ;
	(*env)[0] = ft_strdup("SHLVL=1");
	(*env)[1] = ft_strdup("TERM=xterm-256color");
	(*env)[2] =
ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki");
	(*env)[3] = ft_strdup("USER=liton");
	(*env)[4] = NULL;
}

static char				**env_main(int ac, char **envp)
{
	char	**env;

	env = NULL;
	if (ac != 1)
		return (NULL);
	if (envp && envp[0])
		env = strcpy_env(envp);
	else
		env_null(&env);
	return (env);
}

int						main(int ac, char **av, char **envp)
{
	char		**env;
	char		*builtins;
	char		*cmd;

	(void)av;
	if ((env = env_main(ac, envp)) == NULL)
		return (-1);
	while (42)
	{
		cmd = read_cmd();
		builtins = parsing(cmd);
		if (builtins != NULL)
		{
			ft_builtins(&env, cmd, builtins);
			ft_strdel(&builtins);
		}
		else if (cmd && check_cmd(cmd) != -1)
			exec_command(&env, cmd);
		ft_strdel(&cmd);
	}
	free_env(env);
	return (0);
}
