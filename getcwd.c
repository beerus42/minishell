/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 22:41:14 by liton             #+#    #+#             */
/*   Updated: 2017/08/01 23:18:06 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(int size)
{
	char	*str;
	char	buff[size + 1];

	str = getcwd((char*)buff, size);
//	printf("strr = %s\n", str);
	printf("strr = %s\n", str);
	return (str);
}
