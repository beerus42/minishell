/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:03:45 by liton             #+#    #+#             */
/*   Updated: 2017/09/06 19:17:57 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*my_strcpy(int i, char *error)
{
	char	str[i + 1];
	int		j;

	j = -1;
	while (++j <= i)
		str[j] = error[j];
	str[j] = '\0';
	error = str;
	return (error);
}

void			error_msg(char *error, char *file)
{
	if (file)
	{
		ft_putstr_fd(error, 2);
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(file, 2);
		ft_putchar_fd('\n', 2);
	}
}

void			command_not_found(char *error)
{
	char	*str;
	int		i;

	i = 0;
	if (!error || !error[0])
		return ;
	while (error[i + 1] && error[i + 1] != ' ')
		++i;
	str = my_strcpy(i, error);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void			error_cd(char *path, char *av)
{
	struct stat		buf;

	if (!stat(path, &buf)
			&& !(S_ISDIR(buf.st_mode)) && ft_strcmp(av, "-"))
		error_msg("cd: not a directory:", av);
	else if (!stat(path, &buf)
			&& !(buf.st_mode & S_IXUSR) && ft_strcmp(av, "-"))
		error_msg("cd: permission denied:", av);
	else if (av && ft_strcmp(av, "-"))
		error_msg("cd: no such file or directory:", av);
}

void			split_exec_command(char ***env, char *av)
{
	if (av && (!ft_strcmp(av, "minishell") ||
(ft_strchr(av, '/') && !ft_strcmp(ft_strrchr(av, '/') + 1, "minishell"))))
		change_shlvl(env);
}
