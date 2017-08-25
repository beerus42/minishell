/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 20:05:12 by liton             #+#    #+#             */
/*   Updated: 2017/08/25 02:56:26 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include "../libft/libft.h"

const char		*parsing(char *cmd);
void			command_not_found(char *error);
void			ft_builtins(char ***env, char *cmd, char *builtins);
void			command_env(char **env, char *cmd, char *builtins);
void			free_string(char **str);
void			binary_cd(char ***env, char *cmd);
char			*ft_getcwd(int size);
int				search_v(char **env, char *str);
char			**add_v(char **env, char *variable, char *value);
int				size_env(char **env);
void			free_env(char **env);
void			command_unsetenv(char ***env, char *cmd, char *builtins);
void			command_setenv(char ***env, char *cmd, char *builtins);
void			modify_v(char **env, int p, char *var, char *val);
void			error_msg(char *error, char *file);

#endif
