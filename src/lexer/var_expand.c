/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:35:03 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/18 17:15:09 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

t_list	*expand_standalone_var(t_token *tok)
{
	char	*var_expanded;

	var_expanded = 
	// 2)If contains whitespaces, split and create a list and return
	// 3)if doesnt contain whitecpaces, create a list entry and return
}

t_list	*expand_var_in_dquotes(t_token git *tok)
{
	// 0)Find $ placements
	// 1)get var strrepr char*
	// 2)Write a function that replaces smth in the middle of the str
	//			str_repl(char *where_to_put_src, int len_to_replace, char *what_to_insert)
	// 3)Run this cmd until all variables are expanded, starting from right after the end of the last expansion.
}

t_list	*expand_var_token(t_token *tok)
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
			expanded = expand_var_token((t_token *)(cur->content));
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
