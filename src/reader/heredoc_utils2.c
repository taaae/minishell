/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:07:09 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/03 21:07:47 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

char	*alloc_toklist_to_str_mem(t_list *toks)
{
	char	*res_mem;
	int		res_len;

	res_len = 0;
	res_mem = NULL;
	if (toks == NULL)
		return (NULL);
	while (toks)
	{
		res_len += ((t_token *)(toks->content))->token_len + 1;
		if (((t_token *)(toks->content))->type == TOK_WORD_IN_QUOTES
			|| ((t_token *)(toks->content))->type == TOK_WORD_IN_DQUOTES)
			res_len += 2;
		toks = toks->next;
	}
	res_mem = ft_calloc(res_len + 1, sizeof(char));
	return (res_mem);
}
