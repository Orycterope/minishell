/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 16:03:53 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/28 17:03:18 by tvermeil         ###   ########.fr       */
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
	else if (ft_strcmp(args[1], "cd") == 0 || ft_strcmp(args[1], "env") == 0
			|| ft_strcmp(args[1], "setenv") == 0
			|| ft_strcmp(args[1], "unsetenv") == 0
			|| ft_strcmp(args[1], "where") == 0)
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

static void	exit_cmd(char **args, char **env)
{
	free_tab(env);
	free_tab(args);
	exit(0);
}

static void	clear_cmd(void)
{
	ft_putstr("\x1B[2J");
	ft_putstr("\x1B[1H");
}

int			handle_builtins(char **args, char ***env)
{
	if (ft_strcmp(args[0], "cd") == 0)
		change_directory(args, *env);
	else if (ft_strcmp(args[0], "env") == 0)
		print_env(*env);
	else if (ft_strcmp(args[0], "setenv") == 0)
		set_env_var(args[1], env);
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		rem_env_var(args, env);
	else if (ft_strcmp(args[0], "where") == 0)
		where(args, *env);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit_cmd(args, *env);
	else if (ft_strcmp(args[0], "clear") == 0)
		clear_cmd();
	else
		return (0);
	return (1);
}
