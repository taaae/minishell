/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expand_file_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:03:29 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/22 13:49:46 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "lexer.h"
#include "libft.h"

static int	count_files_in_cur_dir(void)
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

static void	scan_files_in_dir(char ***files, int files_count, \
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

char	**get_files_in_cur_dir(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			**files;
	int				files_count;

	dir = NULL;
	files_count = count_files_in_cur_dir();
	d = opendir(".");
	if (!d)
		return (NULL);
	files = (char **)ft_calloc(files_count + 1, sizeof(char *));
	if (files == NULL)
	{
		closedir(d);
		return (NULL);
	}
	scan_files_in_dir(&files, files_count, d, dir);
	closedir(d);
	return (files);
}
