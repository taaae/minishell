/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expander_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:03:29 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/15 17:27:27 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "lexer.h"
#include "libft.h"

char	*expand_string(char *pattern);

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

void	scan_dir(char ***files, int files_count, DIR *d, struct dirent *dir)
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
	int				i;

	files_count = count_files_in_cur_dir();
	d = opendir(".");
	if (!d)
		return (NULL);
	files = (char **)ft_calloc(files_count + 1, sizeof(char *));
	if (files == NULL)
		return (NULL);
	scan_dir(&files, files_count, d, dir);
	closedir(d);
	return (files);
}

t_list	*expand_token(t_token *tok)
{
	t_list	*new_tok_lst;
	char	*expanded_str;

	expanded_str = expand_string(tok->token_string);
	if (expanded_str == NULL)
		return (NULL);
	return (tokenize(expanded_str));
}

/**
 * @brief Takes token list, returns tok list with all stars expanded
 *
 * Every time it finds a token node that has * in its str_repr,
 * it expands it to a token list, and replaces the node with this list.
 * It should be able to expand 1st and last node of the list.
 * @param tok_lst
 * @return int
 */
int		expand_all_tokens(t_token *tok_lst);

// 4) Написать функцию, которая идёт по списку, и если находит токен со звездой,
// запускает токен_экспандер,
//    и вставляет возвращённый список в лист, не забыв осободить память токена,
// который хранил строку со звездой.
