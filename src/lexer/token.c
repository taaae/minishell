/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:34:51 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/14 17:36:33 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "config.h"
#include "lexer.h"
#include "libft.h"

void	del_token(void *token)
{
	t_token	*tok;

	tok = (t_token *)token;
	if (tok->token_string != NULL)
		free(tok->token_string);
	free(tok);
	return ;
}

char	*str_to_tok_str(char **line)
{
	char	*tok_str;
	int		tok_len;

	tok_len = get_next_tok_len(*line);
	if (tok_len == 0)
		return (NULL);
	tok_str = (char *)ft_calloc(tok_len + 1, sizeof(char));
	if (tok_str == NULL)
		return (NULL);
	tok_str = ft_strncpy(tok_str, *line, tok_len);
	(*line) += tok_len;
	return (tok_str);
}

t_token	*tok_str_to_token(char *tok_str)
{
	t_token	*token;

	if (tok_str == NULL)
		return (NULL);
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
	{
		free(tok_str);
		return (NULL);
	}
	token->token_len = ft_strlen(tok_str);
	token->type = get_token_type(tok_str, token->token_len);
	token->token_string = tok_str;
	return (token);
}

t_list	*token_to_list_entry(t_token *token)
{
	t_list	*entry;

	if (token == NULL)
		return (NULL);
	if (token->type == TOK_ERROR)
	{
		del_token(token);
		return (NULL);
	}
	entry = ft_lstnew(token);
	if (entry == NULL)
		del_token(token);
	return (entry);
}
