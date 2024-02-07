/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_parens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:49:13 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/07 17:49:29 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "lexer.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>


int	quotes_are_correct(char *line)
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

int	check_paren_validity(t_list *tokens)
{
	int		unclosed_paren;
	t_token	*token;

	unclosed_paren = 0;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->type == TOK_OPEN_PARENTH)
			++unclosed_paren;
		else if (token->type == TOK_CLOSE_PARENTH)
			--unclosed_paren;
		if (unclosed_paren < 0)
		{
			ft_putstr_fd("Minishell: Mismatched parentheses\n", STDERR_FILENO);
			return (false);
		}
		tokens = tokens->next;
	}
	if (unclosed_paren)
		ft_putstr_fd("Minishell: Unclosed parentheses\n", STDERR_FILENO);
	return (!unclosed_paren);
}

bool	check_quotes_validity(char *line)
{
	if (!quotes_are_correct(line))
	{
		ft_putstr_fd("Minishell: Unclosed quotes\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}