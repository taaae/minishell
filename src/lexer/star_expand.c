/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:55:50 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/18 13:31:36 by lporoshi         ###   ########.fr       */
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
	int				i;

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

static char	*compose_expansion_str(char *pattern, char **candidates)
{
	char	*expansion;
	char	*temp;
	int		i;

	expansion = ft_strdup("");
	if (expansion == NULL)
		return (NULL);
	i = 0;
	while (candidates[i] != NULL)
	{
		if (match_wildcard(candidates[i], pattern) == FT_TRUE)
		{
			if (append_expansion_str(&expansion, candidates[i]) == FT_ERROR)
				return (NULL);
			if (candidates[i + 1] != NULL)
			{
				if (append_expansion_str(&expansion, " ") == FT_ERROR)
					return (NULL);
			}
		}
		i++;
	}
	return (expansion);
}

static char	*expand_star_string(char *pattern)
{
	char	**files;
	char	*expansion;

	files = get_files_in_cur_dir();
	if (files == NULL)
		return (NULL);
	expansion = compose_expansion_str(pattern, files);
	free_str_arr(&files);
	return (expansion);
}

static t_list	*expand_star_token(t_token *tok)
{
	t_list	*new_tok_lst;
	char	*expanded_str;

	expanded_str = expand_star_string(tok->token_string);
	if (expanded_str == NULL)
		return (NULL);
	return (tokenize(expanded_str));
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
