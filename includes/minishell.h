/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 20:05:12 by liton             #+#    #+#             */
/*   Updated: 2017/08/31 16:57:59 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include "../libft/libft.h"

void			command_not_found(char *error);
void			command_env(char **env, char *cmd, char *builtins);
void			free_string(char **str);
void			binary_cd(char ***env, char *cmd);
int				search_v(char **env, char *str);
char			**add_v(char **env, char *variable, char *value, int bol);
int				size_env(char **env);
void			free_env(char **env);
void			command_unsetenv(char ***env, char *cmd);
void			command_setenv(char ***env, char *cmd);
void			modify_v(char **env, int p, char *var, char *val);
void			error_msg(char *error, char *file);
void			command_exit(char *cmd);
void			exec_command(char ***env, char *cmd);
void			command_echo(char *cmd);
void			free_cd(char **av, char *dir, char *path, int bol);

#endif
