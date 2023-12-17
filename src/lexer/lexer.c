/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:15:04 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/16 14:46:58 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "config.h"
#include "lexer.h"
#include "libft.h"
#include <stdbool.h>

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

	tokens = tokenize(line);
	if (tokens == NULL)
		return (tokens);
	expand_all_tokens(&tokens);
	// expand_variables(&tokens);
	return (tokens);
}
