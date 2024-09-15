/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize_environment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:10:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 01:23:30 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**create_myenv(t_env **env)
{
	char	*cwd;

	add_to_back_env(env, new_env("OLDPWD", NULL));
	add_to_back_env(env, new_env(ft_strdup_env("SHLVL"), ft_strdup_env("0")));
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("shell-init: error retrieving current directory: getcwd:"\
		"cannot access parent directories: No such file or directory\n", 2);
		return (env);
	}
	add_to_back_env(env, new_env("PWD", ft_strdup_env(cwd)));
	free(cwd);
	return (env);
}

void	env_init(char **env, t_env **init_env)
{
	int		i;
	int		j;
	char	c[2];
	char	*key;
	char	*value;

	i = -1;
	while (env && env[++i])
	{
		j = 0;
		key = NULL;
		value = NULL;
		while (env && env[i][j] && env[i][j] != '=')
		{
			ft_strcpy(c, env[i][j++]);
			key = ft_strjoin_env(key, c);
		}
		j++;
		while (env && env[i][j])
		{
			ft_strcpy(c, env[i][j++]);
			value = ft_strjoin_env(value, c);
		}
		add_to_back_env(init_env, new_env(key, value));
	}
}

t_env	**init_environment(char **env)
{
	t_env	**init_env;

	init_env = tmalloc(sizeof(t_env *));
	if (!init_env)
		exiter(1, "malloc");
	*init_env = NULL;
	if (!*env)
		return (create_myenv(init_env));
	env_init(env, init_env);
	return (init_env);
}
