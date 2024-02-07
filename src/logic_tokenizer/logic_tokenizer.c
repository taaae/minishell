/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:49:01 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/07 17:51:39 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "logic_tokenizer.h"

int				alloc_log_toks(t_logic_token ***tokens, char *line);
void			fill_log_toks(t_logic_token **tokens, int tok_amt, char *line);

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

	tok_amt = alloc_log_toks(&tokens, line);
	if (tokens == NULL)
		return (NULL);
	fill_log_toks(tokens, tok_amt, line);
	return (tokens);
}
