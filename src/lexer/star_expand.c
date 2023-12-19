/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:55:50 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/18 15:34:22 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

static char	**get_files_in_cur_dir(void)
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
		return (NULL);
	scan_files_in_dir(&files, files_count, d, dir);
	closedir(d);
	return (files);
}

static char	**compose_expansion_arr(char *pattern, char **candidates)
{
	char	**expansion;
	char	**expansion_orig;
	int		i;
	int		sz;

	i = 0;
	sz = 0;
	while (candidates[i] != NULL)
		if (match_wildcard(candidates[i++], pattern) == FT_TRUE)
			sz++;
	expansion = (char **)ft_calloc(sz + 2, sizeof(char *));
	if (expansion == NULL)
		return (NULL);
	expansion_orig = expansion;
	i = 0;
	while (candidates[i] != NULL)
	{
		if (match_wildcard(candidates[i], pattern) == FT_TRUE)
			*(expansion++) = ft_strdup(candidates[i]);
		i++;
	}
	return (expansion_orig);
}

static char	**expand_star_string(char *pattern)
{
	char	**files;
	char	**expansion;

	files = get_files_in_cur_dir();
	if (files == NULL)
		return (NULL);
	expansion = compose_expansion_arr(pattern, files);
	free_str_arr(&files);
	return (expansion);
}

static t_list	*expand_star_token(t_token *tok)
{
	t_list	*expanded_lst;
	t_list	*expanded_entry;
	char	**expansion_list;
	int		i;

	expanded_lst = NULL;
	expansion_list = expand_star_string(tok->token_string);
	if (expansion_list == NULL)
		return (NULL);
	i = 0;
	while (expansion_list[i] != NULL)
	{
		expanded_entry = expanded_star_to_token(expansion_list[i++]);
		if (expanded_entry == NULL)
		{
			ft_lstclear(&expanded_lst, del_token);
			free_str_arr(&expansion_list);
			return (NULL);
		}
		ft_lstadd_back(&expanded_lst, expanded_entry);
	}
	free_str_arr(&expansion_list);
	return (expanded_lst);
}

int	expand_all_stars(t_list **tok_lst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*expanded;

	prev = NULL;
	cur = *tok_lst;
	while (cur != NULL)
	{
		if (ft_in('*', ((t_token *)(cur->content))->token_string))
		{
			expanded = expand_star_token((t_token *)(cur->content));
			if (expanded == NULL)
				((t_token *)(cur->content))->type = TOK_ERROR;
			else
			{
				cur = lst_replace_node_to_list(prev, &cur, expanded);
				if (prev == NULL)
					*tok_lst = expanded;
			}
		}
		prev = cur;
		if (cur != NULL)
			cur = cur->next;
	}
	return (FT_SUCCESS);
}
