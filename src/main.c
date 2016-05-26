/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:35:41 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/26 17:40:41 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <signal.h>

int		g_child_pid = 0;

void	sig_handler(int sig)
{
	if (g_child_pid != 0)
		kill(g_child_pid, sig);
	ft_putchar('\n');
	if (g_child_pid == 0)
		ft_putstr(PROMPT);
}

void	execute(char **arg_list, char ***env)
{
	char	*bin_path;

	if (handle_builtins(arg_list, env) != 0)
		return ;
	if ((bin_path = find_binary(*env, arg_list[0])) == NULL)
	{
		ft_printf("minishell: no executable file found: %s\n", arg_list[0]);
		return ;
	}
	if ((g_child_pid = fork()) == 0)
	{
		if (execve(bin_path, arg_list, *env))
			ft_printf("minishell: error during execution of %s\n", bin_path);
		exit(0);
	}
	else
	{
		wait(NULL);
		free(bin_path);
	}
	g_child_pid = 0;
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
	signal(SIGINT, sig_handler);
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

void	free_tab(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i] != NULL)
		free(tab[i]);
	free(tab);
}
