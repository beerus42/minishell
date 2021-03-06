/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_v.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 02:12:47 by liton             #+#    #+#             */
/*   Updated: 2017/09/06 23:32:36 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				support_setenv(char **env, char ***av)
{
	if (!env || !(*av)[1] || ft_strchr((*av)[1], '='))
	{
		if ((*av)[1] == NULL)
			ft_display_tab(env);
		else if ((*av)[1] && ft_strchr((*av)[1], '='))
			ft_putstr_fd("setenv: variable or value can't contain '='.\n", 2);
		free_env(*av);
		return (-1);
	}
	return (0);
}

void			modify_v(char **env, int p, char *var, char *val)
{
	int		i;
	int		j;
	char	str[ft_strlen(var) + ft_strlen(val) + 2];

	i = -1;
	j = -1;
	while (var && var[++i])
		str[i] = var[i];
	str[i++] = '=';
	while (val && val[++j])
		str[i++] = val[j];
	str[i] = '\0';
	ft_strdel(&env[p]);
	env[p] = ft_strdup(str);
}

int				size_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		++i;
	return (i);
}

static void		cpy_var(char **env, int i, char *variable, char *value)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (variable && variable[j])
	{
		env[i][j] = variable[j];
		++j;
	}
	env[i][j] = '=';
	++j;
	while (value && value[k])
	{
		env[i][j] = value[k];
		++k;
		++j;
	}
	env[i][j] = '\0';
}

char			**add_v(char **env, char *variable, char *value)
{
	int		i;
	int		var;
	int		val;
	char	**new_env;

	i = -1;
	var = ft_strlen(variable);
	val = ft_strlen(value);
	if (!(new_env = (char**)malloc(sizeof(char*) * (size_env(env) + 2))))
		return (NULL);
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	if (!(new_env[i] = (char*)malloc(sizeof(char) * (var + val + 2))))
		return (NULL);
	cpy_var(new_env, i, variable, value);
	new_env[i + 1] = NULL;
	free_env(env);
	return (new_env);
}
