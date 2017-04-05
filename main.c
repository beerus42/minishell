/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 19:56:19 by liton             #+#    #+#             */
/*   Updated: 2017/04/05 00:08:17 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av)
{
	char	buf[6 + 1];
	char	*save;
	char	ls[3] = "ls";
	int		ret;

	(void)ac;
	(void)av;
	save = ft_strnew(0);
	ft_putstr_fd("$> ", 0);
	while ((ret = read(0, buf, 6)) > 0)
	{
		buf[ret] = '\0';
		save = ft_strjoinfree(save, buf, 0);
		if (ft_strchr(save, '\n'))
			break ;
	}
	save = ft_strdup("ls");
	if (!ft_strcmp(save, ls))
		execve("/bin/ls", av, NULL);
}
