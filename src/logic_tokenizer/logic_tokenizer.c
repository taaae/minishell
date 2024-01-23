/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:49:01 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/23 14:46:27 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "logic_tokenizer.h"

int		alloc_log_toks(t_logic_token ***tokens, char *line);
void	fill_log_toks(t_logic_token **tokens, int tok_amt, char *line);

static int	quotes_are_correct(char *line)
{
	while (*line)
	{
		if (*line == '\'')
		{
			line++;
			while (*line && *line != '\'')
				line++;
			if (*line == '\0')
				return (0);
		}
		else if (*line == '"')
		{
			line++;
			while (*line && *line != '"')
				line++;
			if (*line == '\0')
				return (0);
		}
		line++;
	}
	return (1);
}

void	skip_quotes(char **line)
{
	char	quote;
	char	*s;

	s = *line;
	quote = *s++;
	while (*s != quote)
		s++;
	s++;
	*line = s;
	return ;
}

static int	parens_are_correct(char *line)
{
	int	stack;

	stack = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '"')
			skip_quotes(&line);
		if (*line == '\0')
			return (stack == 0);
		if (*line == '(')
			stack++;
		else if (*line == ')')
			stack--;
		if (stack < 0)
			return (0);
		line++;
	}
	return (stack == 0);
}

t_logic_token	**logic_split(char *line)
{
	t_logic_token	**tokens;
	int				tok_amt;

	if (!quotes_are_correct(line) || !parens_are_correct(line))
		return (NULL);
	tok_amt = alloc_log_toks(&tokens, line);
	if (tokens == NULL)
		return (NULL);
	fill_log_toks(tokens, tok_amt, line);
	return (tokens);
}
