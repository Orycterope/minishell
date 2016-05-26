/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:35:41 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/26 15:52:43 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>

void	execute(char **arg_list, char ***env)
{
	pid_t	pid;
	char	*bin_path;
	//int	res;

	if (handle_builtins(arg_list, env) != 0)
		return ;
	if ((bin_path = find_binary(*env, arg_list[0])) == NULL)
	{
		ft_printf("minishell: no executable file found: %s\n", arg_list[0]);
		return ;
	}
	if ((pid = fork()) == 0)
	{
		execve(bin_path, arg_list, *env);
		exit(0);
	}
	else
	{
		wait(NULL);
		free(bin_path);
	}
}

int		main(int ac, char **av, char **env)
{
	char	*line_command;
	char	*sanitized_line_command;
	char	**arg_list;

	(void)ac;
	(void)av;
	ft_putstr(PROMPT);
	env = copy_env(env, 0);
	while (get_next_line(0, &line_command))
	{
		sanitized_line_command = ft_strsanitize(line_command);
		free(line_command);
		if (sanitized_line_command)
		{
			arg_list = ft_strsplit(sanitized_line_command, ' ');
			free(sanitized_line_command);
			execute(arg_list, &env);
			free_tab(arg_list);
		}
		ft_putstr(PROMPT);
	}
	ft_putendl("exit");
	free_tab(env);
	return (0);
}
