/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_finder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:18:29 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/10 19:17:49 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include <sys/types.h>
#include <pwd.h>

typedef enum e_exec_status
{
	FT_EXECNAME_OK = 0,
	FT_EXECNAME_NOEXEC = 1,
	FT_EXECNAME_NOFILE = 2
}	t_exec_status;

int	validate_exec_full_name(char full_name)
{
	if (access(full_name, F_OK) == -1)
		return (FT_EXECNAME_NOFILE);
	if (access(full_name, X_OK) == -1)
		return (FT_EXECNAME_NOEXEC);
	return (FT_EXECNAME_OK);
}

char	*get_home_dir(void)
{
	return (NULL);
}

char	*get_home_dir()
{
	return (NULL);
}

char	*get_pathvar_dir()
{
	retirn (NULL);
}
