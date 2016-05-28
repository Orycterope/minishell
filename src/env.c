/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 18:02:14 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/28 15:14:22 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	print_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
}

char	*get_env_var(char *var, char **env)
{
	char	*intermediate;
	int		i;
	int		length;

	if (env == NULL || var == NULL)
		return (NULL);
	intermediate = ft_strjoin(var, "=");
	if (intermediate == NULL)
		return (NULL);
	length = ft_strlen(intermediate);
	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strstr(env[i], intermediate) == env[i])
			break ;
	}
	free(intermediate);
	if (env[i] == NULL)
		return (NULL);
	else
		return (env[i] + length);
}

void	add_env_var(char *arg, char ***env)
{
	char	**new;
	int		i;

	new = copy_env(*env, 1);
	if (new == NULL)
		return ;
	i = 0;
	while ((*env)[i] != NULL)
		i++;
	new[i] = ft_strdup(arg);
	new[i + 1] = NULL;
	free(*env);
	*env = new;
}

void	rem_env_var(char **args, char ***env)
{
	char	**new;
	int		i;
	char	*var;

	if (args[1] == NULL)
	{
		ft_putendl("unsetenv: not enough arguments");
		return ;
	}
	if ((var = get_env_var(args[1], *env)) == NULL)
		return ;
	var -= ft_strlen(args[1]) + 1;
	new = copy_env(*env, -1);
	if (new == NULL)
		return ;
	i = -1;
	while ((*env)[++i] != var)
		new[i] = (*env)[i];
	while ((*env)[++i] != NULL)
		new[i - 1] = (*env)[i];
	new[i - 1] = NULL;
	free(var);
	free(*env);
	*env = new;
}

void	set_env_var(char *arg, char ***env)
{
	int		i;
	char	*sub;

	if (arg == NULL)
	{
		ft_putendl("setenv: not enough arguments");
		return ;
	}
	if (ft_strchr(arg, '=') == NULL || ft_strchr(arg, '=') == arg)
		return ;
	sub = ft_strsub(arg, 0, ft_strchr(arg, '=') - arg);
	i = -1;
	while ((*env)[++i])
		if (ft_strstr((*env)[i], sub) == (*env)[i])
		{
			free(sub);
			free((*env)[i]);
			(*env)[i] = ft_strdup(arg);
			return ;
		}
	free(sub);
	add_env_var(arg, env);
}
