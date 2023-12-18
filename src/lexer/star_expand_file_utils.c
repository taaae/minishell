/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expander_file_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:03:29 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/18 13:33:36 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "lexer.h"
#include "libft.h"

int	count_files_in_cur_dir(void)
{
	DIR				*d;
	struct dirent	*dir;
	int				i;

	d = opendir(".");
	if (!d)
		return (FT_ERROR);
	i = 0;
	dir = readdir(d);
	while (dir != NULL)
	{
		i++;
		dir = readdir(d);
	}
	closedir(d);
	return (i);
}

void	scan_files_in_dir(char ***files, int files_count, \
DIR *d, struct dirent *dir)
{
	int	i;

	i = 0;
	while (i < files_count)
	{
		dir = readdir(d);
		if (dir == NULL)
		{
			free_str_arr(files);
			return ;
		}
		(*files)[i] = ft_strdup(dir->d_name);
		if ((*files)[i] == NULL)
		{
			free_str_arr(files);
			return ;
		}
		i++;
	}
	return ;
}
