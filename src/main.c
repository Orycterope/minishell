/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:35:41 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/24 17:12:48 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>

void	execute(char **arg_list, char **env)
{
	pid_t	pid;
	//int		res;

	(void)arg_list;
	(void)env;
	if ((pid = fork()) == 0)
	{
		execve(ft_strjoin("/bin/", arg_list[0]), arg_list, env);
		exit(0);
	}
	else
	{
		wait(NULL);
	}
}

int		main(int ac, char **av, char **env)
{
	char	*line_command;
	char	*sanitized_line_command;
	char	**arg_list;
	int		i;

	(void)ac;
	(void)av;
	ft_putstr(PROMPT);
	while (get_next_line(0, &line_command))
	{
		sanitized_line_command = ft_strsanitize(line_command);
		free(line_command);
		if (sanitized_line_command)
		{
			arg_list = ft_strsplit(sanitized_line_command, ' ');
			free(sanitized_line_command);
			execute(arg_list, env);
			i = 0;
			while (arg_list[i])
				free(arg_list[i++]);
		}
		ft_putstr(PROMPT);
	}
	ft_putendl("exit");
	return (0);
}
