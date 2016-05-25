/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 14:54:02 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/25 15:59:25 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

static char	**get_path_tab(char **env)
{
	int		i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strstr(env[i], "PATH=") == env[i])
			return (ft_strsplit(env[i] + 5, ':'));
	}
	return (NULL);
}

char	*find_binary(char **env, char *bin_name)
{
	char	**path_tab;
	char	*attempt;
	char	*intermediate;
	int		i;

	path_tab = get_path_tab(env);
	if (path_tab == NULL)
		return (NULL);
	i = -1;
	while (path_tab[++i])
	{;
		intermediate = ft_strjoin(path_tab[i], "/");
		attempt = ft_strjoin(intermediate, bin_name);
		free(intermediate);
		if (access(attempt, X_OK) == 0)
			return (attempt);
		free(attempt);
	}
	ft_printf("minishell: no executable file found: %s\n", bin_name);
	return (NULL);
}
