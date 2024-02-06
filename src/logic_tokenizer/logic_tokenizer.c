/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:49:01 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/03 19:04:30 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "logic_tokenizer.h"

int				alloc_log_toks(t_logic_token ***tokens, char *line);
void			fill_log_toks(t_logic_token **tokens, int tok_amt, char *line);

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

t_logic_token	**logic_split(char *line)
{
	t_logic_token	**tokens;
	int				tok_amt;

	if (!quotes_are_correct(line))
	{
		ft_putendl_fd("unclosed quotes\n", STDERR_FILENO);
		return (NULL);
	}
	tok_amt = alloc_log_toks(&tokens, line);
	if (tokens == NULL)
		return (NULL);
	fill_log_toks(tokens, tok_amt, line);
	return (tokens);
}
