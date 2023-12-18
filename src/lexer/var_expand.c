/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:35:03 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/18 17:43:28 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "environment.h"

void	replace_var(char *str)
{
	// 2)Write a function that replaces smth in the middle of the str
	//		str_repl(char *where_to_put_src, int len_to_replace, char *what_to_insert)
	// We are standing at $ sym
	// 1. Find where the variable name ends
	// 2. Cut this piece and call ft_getenv on the cut part
	// 3. insert what it returned instead of var name
	// profit
}

t_list	*expand_var_in_dquotes(t_token git *tok)
{
	char	*cur;

	cur = tok->token_string;
	while (*cur != '\0')
	{
		if (*cur == '$')
			replace_var(cur);
		else
			cur++;
	}
	tok->token_len = ft_strlen(token->token_string);
}

t_list	*split_and_tokenize(char *str)
{
	char	**split;
	t_list	*res_list;
	t_list	*cur_entry;
	int		i;

	split = ft_split(str, ' ');
	if (split == NULL || split[0] == NULL)
		return (NULL);
	free(str);
	i = 0;
	res_list = ft_lstnew();
	while (split[i])
	{
		ft_lstadd_back(&res_list);
	}
	// We have a string that contains spaces
	// We spilt it and for every entry create a
	// t_list entry with content = token(split_entry)
	// with type WORD
	// And return the list.
}

t_list	*expand_standalone_var(t_token *tok)
{
	char	*var_expanded;
	char	**var_split;
	t_list	*result_list;

	var_expanded = ft_getenv(tok->token_string);
	if (var_expanded == NULL || !ft_in(' ', var_expanded))
	{
		free(tok->token_string);
		if (var_expanded == NULL)
			tok->token_string = ft_strdup("");
		else
			tok->token_string = var_expanded;
		tok->type = TOK_WORD;
		tok->token_len = ft_strlen(tok->token_string);
		return (NULL);
	}
	result_list = split_and_tokenize(var_expanded);
	if (result_list == NULL)
		tok->token_type = TOK_ERROR;
	return (result_list);
}

t_list	*expand_var_token(t_list *tok_entry)
{
	if (tok->type == TOK_VAR)
		return (expand_standalone_var(tok));
	if (tok->type == TOK_WORD_IN_DQUOTES)
		return (expand_var_in_dquotes(tok));
	return (NULL);
}

static int	contains_var(t_token *tok)
{
	return (tok->type == TOK_VAR || \
	(tok->type == TOK_WORD_IN_DQUOTES && ft_in('$', tok->token_string)));
}

int	expand_all_vars(t_list **tok_lst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*expanded;

	prev = NULL;
	cur = *tok_lst;
	while (cur != NULL)
	{
		if (contains_var((t_token *)(cur->content)))
		{
			expanded = expand_var_token(cur);
			if (expanded != NULL)
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
