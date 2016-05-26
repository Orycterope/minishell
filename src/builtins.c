/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 16:03:53 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/26 14:19:24 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

static void	where(char **args, char **env)
{
	char	*path;

	if (args[1] == NULL)
	{
		ft_putendl("usage: where program");
		return ;
	}
	else if (ft_strcmp(args[1], "cd") == 0 || ft_strcmp(args[1], "env") == 0 ||
			ft_strcmp(args[1], "setenv") == 0 ||ft_strcmp(args[1], "unsetenv") == 0 ||
			ft_strcmp(args[1], "where") == 0)
		path = ft_strdup("shell built-in command");
	else
		path = find_binary(env, args[1]);
	if (path == NULL)
		path = ft_strdup("not found");
	ft_printf("%s: %s\n", args[1], path);
	free(path);
}

static void	change_directory(char **args, char **env)
{
	char	*path;

	if (args[1] == NULL)
		path = get_env_var("HOME", env);
	else
		path = args[1];
	if (path != NULL)
	{
		if (chdir(path) == -1)
			ft_printf("minishell: no such file or directory: %s\n", path);
	}
}

int	handle_builtins(char **args, char ***env)
{
	if (ft_strcmp(args[0], "cd") == 0)
		change_directory(args, *env);
	else if (ft_strcmp(args[0], "env") == 0)
		print_env(*env);
	else if (ft_strcmp(args[0], "setenv") == 0)
		add_env_var(args, env);
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		rem_env_var(args, env);
	else if (ft_strcmp(args[0], "where") == 0)
		where(args, *env);
	else
		return (0);
	return (1);
}
