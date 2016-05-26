/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:46:53 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/26 15:53:10 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PROMPT "$> "

char	*find_binary(char **env, char *bin_name);
int		handle_builtins(char **args, char ***env);
void	print_env(char **env);
char	*get_env_var(char *var, char **env);
char	**copy_env(char **env, int difference);
void	add_env_var(char **args, char ***env);
void	rem_env_var(char **args, char ***env);
void	free_tab(char **tab);

#endif
