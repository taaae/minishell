/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:54:34 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/14 17:36:07 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int	get_token_type_len_2(char *tok_str)
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

int	get_token_type_len_1(const char c)
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

int	get_token_type(char *tok_str, int tok_len)
{
	if (tok_len == 1)
		return (get_token_type_len_1(tok_str[0]));
	if (tok_len == 2)
		return (get_token_type_len_2(tok_str));
	if (tok_str[0] == '\"')
		return (TOK_WORD_IN_DQUOTES);
	if (tok_str[0] == '\'')
		return (TOK_WORD_IN_QUOTES);
	return (TOK_WORD);
}

int	get_next_tok_len(char *line)
{
	int	i;

	i = 0;
	if (ft_in(line[i], ONE_SYM_WORDS))
		return (1);
	if (ft_in(line[i], TWO_SYM_WORDS))
		return (parse_double_sym_word(line + i));
	if (line[i] == '\'')
		return (parse_quotes(line + i));
	if (line[i] == '\"')
		return (parse_dquotes(line + i));
	if (line[i] == '$')
		return (parse_var(line + i));
	return (parse_word(line + i));
}
