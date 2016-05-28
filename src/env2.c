/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 16:04:42 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/28 15:13:42 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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
	if (difference >= 0)
	{
		i = -1;
		while (++i < length - 1)
			new[i] = (difference > 0) ? env[i] : ft_strdup(env[i]);
		new[i] = NULL;
	}
	return (new);
}
