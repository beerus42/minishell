/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 20:05:12 by liton             #+#    #+#             */
/*   Updated: 2017/07/27 20:48:10 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "./libft/libft.h"

char		*read_cmd(void);
int			parsing(char *cmd, char ***cmd_split);
void		command_not_found(char *error);
void		ft_builtins(char **cmd, char **env);
void		command_env(char **cmdd, char **env);

#endif
