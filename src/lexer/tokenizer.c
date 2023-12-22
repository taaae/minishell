/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:15:04 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/22 13:25:44 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "config.h"
#include "lexer.h"
#include "libft.h"
#include <stdbool.h>

bool	check_quotes_validity(char *line)
{
	bool	unclosed_quotes;
	bool	unclosed_dquotes;
	int		unclosed_paren;

	unclosed_quotes = false;
	unclosed_dquotes = false;
	unclosed_paren = 0;
	while (*line)
	{
		if (*line == '\'')
			unclosed_quotes = !unclosed_quotes;
		else if (*line == '\"')
			unclosed_dquotes = !unclosed_dquotes;
		else if (*line == '(')
			++unclosed_paren;
		else if (*line == ')')
			--unclosed_paren;
		line++;
	}
	return (!(unclosed_quotes || unclosed_dquotes || unclosed_paren));
}

void	del_token(void *token)
{
	t_token	*tok;

	tok = (t_token *)token;
	if (tok->token_string != NULL)
		free(tok->token_string);
	free(tok);
	return ;
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

t_list	*tokenize(char *line)
{
	t_list	*token_list;
	t_list	*current_entry;

	if (line == NULL)
		return (NULL);
	while (ft_isspace(*line))
		line++;
	token_list = NULL;
	while (*line != '\0')
	{
		current_entry = token_to_list_entry (\
		tok_str_to_token(str_to_tok_str(&line)));
		if (current_entry == NULL)
		{
			ft_lstclear(&token_list, del_token);
			return (NULL);
		}
		ft_lstadd_back(&token_list, current_entry);
		while (ft_isspace(*line))
			line++;
	}
	return (token_list);
}

t_list	*line_to_tokens(char *line)
{
	t_list	*tokens;

	if (line == NULL || check_quotes_validity(line) == false)
		return (NULL);
	tokens = tokenize(line);
	return (tokens);
}
