/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:03:45 by liton             #+#    #+#             */
/*   Updated: 2017/07/27 22:45:06 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		command_not_found(char *error)
{
	if (!error[0] || !error)
		return ;
	ft_putstr("bash: ");
	ft_putstr(error);
	ft_putstr(": command not found\n");
}
