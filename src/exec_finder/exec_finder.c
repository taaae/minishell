/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:18:29 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/31 18:47:50 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "exec_find.h"
#include "environment.h"
#include "libft.h"

char	*get_pathvar_dir(char *name);
char	*expand_exec_name_pathvar(char *name);
int		validate_exec_full_name(char *full_name);

char	*expand_exec_name_relative(char *name)
{
	char	*current_dir;
	char	*full_name;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
		return (NULL);
	full_name = ft_strjoin(current_dir, "/");
	free(current_dir);
	current_dir = full_name;
	full_name = ft_strjoin(full_name, name);
	free(current_dir);
	return (full_name);
}

char	*expand_exec_name_home(char *name)
{
	char	*home_dir;
	char	*full_name;

	home_dir = ft_getenv("HOME");
	if (home_dir == NULL)
		return (NULL);
	full_name = ft_strjoin(home_dir, name + 1);
	free(home_dir);
	return (full_name);
}

char	*expand_exec_name_pathvar(char *name)
{
	char	*current_dir;
	char	*full_name;

	current_dir = get_pathvar_dir(name);
	if (current_dir == NULL)
		return (NULL);
	full_name = ft_strjoin(current_dir, "/");
	free(current_dir);
	current_dir = full_name;
	full_name = ft_strjoin(full_name, name);
	free(current_dir);
	return (full_name);
}

/**
 * @brief Takes exec name from shell and expands it to full path+name of exec
 * 
 * Searches $PATH, handles relative path, absolute path, ~/...
 * Does not free "name"'s memory
 * Ensures that the file exists and is executable
 * Otherwise returns NULL
 * @param name 
 * @return char* 
 */
char	*expand_exec_name(char *name)
{
	char	*result;

	if (name == NULL || name[0] == '\0')
		return (NULL);
	else if (name[0] == '/')
		result = ft_strdup(name);
	else if (name[0] == '~')
		result = expand_exec_name_home(name);
	else if (name[0] == '.' || ft_in('/', name))
		result = expand_exec_name_relative(name);
	else
		result = expand_exec_name_pathvar(name);
	if (result == NULL || validate_exec_full_name(result) != FT_EXECNAME_OK)
	{
		free(result);
		result = NULL;
	}
	return (result);
}
