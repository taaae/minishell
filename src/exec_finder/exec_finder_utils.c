/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_finder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:18:29 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/31 18:45:44 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include "exec_find.h"
#include "libft.h"
#include "environment.h"

char	**split_path(void)
{
	char	**s;
	char	*pathvar;

	pathvar = ft_getenv("PATH");
	s = ft_split(pathvar, ':');
	free(pathvar);
	return (s);
}

int	validate_exec_full_name(char *full_name)
{
	struct stat	file_stats;

	if (full_name == NULL || stat(full_name, &file_stats) != 0 \
						|| !(S_ISREG(file_stats.st_mode)))
		return (FT_ERROR);
	if (access(full_name, F_OK) == -1)
		return (FT_EXECNAME_NOFILE);
	if (access(full_name, X_OK) == -1)
		return (FT_EXECNAME_NOEXEC);
	return (FT_EXECNAME_OK);
}

int	check_exec(char *path, char *name)
{
	char	*full_name;
	char	*tmp;
	int		result;

	full_name = ft_strjoin(path, "/");
	tmp = full_name;
	full_name = ft_strjoin(full_name, name);
	free(tmp);
	result = validate_exec_full_name(full_name);
	free(full_name);
	return (result);
}

char	*get_pathvar_dir(char *name)
{
	char	**paths;
	char	*result;
	int		i;

	result = NULL;
	paths = split_path();
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		if (check_exec(paths[i], name) == FT_EXECNAME_OK)
		{
			result = ft_strdup(paths[i]);
			break ;
		}
		i++;
	}
	free_str_arr(&paths);
	return (result);
}
