/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_composer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:20:45 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 14:57:10 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static int	get_token_type_len_1(const char c)
{
	if (c == '\'')
		return (TOK_WORD_IN_QUOTES);
	if (c == '\"')
		return (TOK_WORD_IN_DQUOTES);
	if (c == '$')
		return (TOK_WORD);
	if (c == '|')
		return (TOK_PIPE_SYM);
	if (c == '>')
		return (TOK_WRITE_TO_FILE_SYM);
	if (c == '<')
		return (TOK_READ_FROM_FILE_SYM);
	if (c == '(')
		return (TOK_OPEN_PARENTH);
	if (c == ')')
		return (TOK_CLOSE_PARENTH);
	return (TOK_WORD);
}

static int	get_token_type_len_2(char *tok_str)
{
	if (tok_str[0] == tok_str[1])
	{
		if (tok_str[0] == '|')
			return (TOK_OR_SYM);
		if (tok_str[0] == '&')
			return (TOK_AND_SYM);
		if (tok_str[0] == '>')
			return (TOK_APPEND_TO_FILE_SYM);
		if (tok_str[0] == '<')
			return (TOK_HEREDOC_SYM);
	}
	return (TOK_WORD);
}

static int	get_token_type(char *tok_str, int tok_len)
{
	if (tok_len == 1)
		return (get_token_type_len_1(tok_str[0]));
	if (tok_len == 2)
		return (get_token_type_len_2(tok_str));
	if (tok_str[0] == '\"')
		return (TOK_WORD_IN_DQUOTES);
	if (tok_str[0] == '\'')
		return (TOK_WORD_IN_QUOTES);
	if (tok_str[0] == '$')
		return (TOK_VAR);
	return (TOK_WORD);
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
	char	*result_str;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (tok_str == NULL || token == NULL)
	{
		free(token);
		return (NULL);
	}
	token->token_len = ft_strlen(tok_str);
	token->type = get_token_type(tok_str, token->token_len);
	result_str = tok_str;
	if (token->type == TOK_WORD_IN_DQUOTES || token->type == TOK_WORD_IN_QUOTES)
		token->token_len -= 2;
	if (token->type == TOK_WORD_IN_DQUOTES)
		result_str = ft_strtrim(tok_str, "\"");
	else
		result_str = ft_strtrim(tok_str, "\'");
	if (result_str == NULL)
	{
		free(token);
		return (NULL);
	}
	token->token_string = result_str;
	return (token);
}
