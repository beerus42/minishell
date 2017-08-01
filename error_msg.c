/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:03:45 by liton             #+#    #+#             */
/*   Updated: 2017/08/01 02:39:23 by liton            ###   ########.fr       */
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
	ft_putstr("bash: ");
	ft_putstr(str);
	ft_putstr(": command not found\n");
}
