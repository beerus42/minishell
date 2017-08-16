/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:03:45 by liton             #+#    #+#             */
/*   Updated: 2017/08/16 04:59:51 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*my_strcpy(int i, char *error)
{
	char	str[i + 1];
	int		j;

	j = -1;
	while (++j <= i)
		str[j] = error[j];
	str[j] = '\0';
	free_string(&error);
	error = str;
	return (error);
}

void			error_msg(char *error, char *file)
{
	ft_putstr_fd(error, 2);
	if (file)
	{
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(file, 2);
	}
	ft_putchar_fd('\n', 2);
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
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}
