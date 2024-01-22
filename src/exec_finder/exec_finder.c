/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:18:29 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/16 14:27:10 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include <sys/types.h>
#include <pwd.h>

char	*expand_exec_name_relative(char *name)
{
	char	*current_dir;
	char	*full_name;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
		return (NULL);
	full_name = ft_strjoin(current_dir, name);
	free(current_dir);
	return (full_name);
}

char	*expand_exec_name_home(char *name)
{
	char	*home_dir;
	char	*full_name;

	home_dir = get_home_dir();
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
	full_name = ft_strjoin(current_dir, name);
	free(current_dir);
	return (full_name);
}

static char	*expand_exec_name(char *name)
{
	if (name == NULL)
		return (NULL);
	else if (name[0] == '.')
		return (expand_exec_name_relative(name));
	else if (name[0] == '/')
		return (name);
	else if (name[0] == '~')
		return (expand_exec_name_home(name));
	else
		return (expand_exec_name_path(name));
}
