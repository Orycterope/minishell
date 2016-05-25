/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 16:03:53 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/25 19:19:53 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

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
	else
		return (0);
	return (1);
}
