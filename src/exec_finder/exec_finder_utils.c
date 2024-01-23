/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_finder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:18:29 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/23 17:35:34 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "environment.h"
#include <sys/types.h>
#include <pwd.h>

char	**split_path(void);

typedef enum e_exec_status
{
	FT_EXECNAME_OK = 0,
	FT_EXECNAME_NOEXEC = 1,
	FT_EXECNAME_NOFILE = 2
}	t_exec_status;

int	validate_exec_full_name(char *full_name)
{
	if (full_name == NULL)
		return (FT_ERROR);
	if (access(full_name, F_OK) == -1)
		return (FT_EXECNAME_NOFILE);
	if (access(full_name, X_OK) == -1)
		return (FT_EXECNAME_NOEXEC);
	return (FT_EXECNAME_OK);
}

char	*get_home_dir(void)
{
	return (ft_getenv("$HOME"));
}

int	check_exec(char *path, char *name)
{
	char	*full_name;
	int		result;

	ft_printf("%s/%s\n", path, name);
	full_name = ft_strjoin(path, name);
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
