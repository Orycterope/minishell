/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 14:54:02 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/26 15:37:35 by tvermeil         ###   ########.fr       */
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

static void free_path_tab(char **path_tab)
{
	int		i;

	i = -1;
	while (path_tab[++i] != NULL)
		free(path_tab[i]);
	free(path_tab);
}

static char	*find_bin_in_path(char *bin_name, char **path_tab)
{
	int		i;
	char	*attempt;
	char	*intermediate;

	i = -1;
	while (path_tab[++i])
	{
		intermediate = ft_strjoin(path_tab[i], "/");
		attempt = ft_strjoin(intermediate, bin_name);
		free(intermediate);
		if (access(attempt, X_OK) == 0)
		{
			free_path_tab(path_tab);
			return (attempt);
		}
		free(attempt);
	}
	free_path_tab(path_tab);
	return (NULL);
}

char		*find_binary(char **env, char *bin_name)
{
	char	**path_tab;

	if (ft_strchr(bin_name, '/') != NULL)
	{
		if (access(bin_name, X_OK) == 0)
			return (ft_strdup(bin_name));
		else
			return (NULL);
	}
	path_tab = get_path_tab(env);
	if (path_tab == NULL)
		return (NULL);
	return find_bin_in_path(bin_name, path_tab);
}
