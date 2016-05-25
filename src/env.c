/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 18:02:14 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/25 19:31:44 by tvermeil         ###   ########.fr       */
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

char	**copy_env(char **env, int difference)
{
	char	**new;
	int		length;
	int		new_length;
	int		i;

	length = 0;
	while (env[length] != NULL)
		length++;
	length++;
	new_length = length + difference;
	new = (char **)malloc(sizeof(char *) * new_length);
	if (new == NULL)
		return (NULL);
	i = -1;
	while (++i < length)
		new[i] = env[i];
	return (new);
}

void	add_env_var(char **args, char ***env)
{
	char	**new;
	int		i;

	if (args[1] == NULL)
	{
		ft_putendl("setenv: not enough arguments");
		return ;
	}
	if (ft_strchr(args[1], '=') == NULL)
		return ;
	new = copy_env(*env, 1);
	if (new == NULL)
		return ;
	i = 0;
	while ((*env)[i] != NULL)
		i++;
	new[i] = ft_strdup(args[1]);
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
		ft_putendl("setenv: not enough arguments");
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
	free(*env);
	*env = new;
}
