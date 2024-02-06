/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_tokenizer_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:38:53 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 13:55:17 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "logic_tokenizer.h"

static int	skip_token(char **lineptr)
{
	if (**lineptr == '\0')
		return (0);
	while (ft_isspace((*lineptr)[0]))
		(*lineptr)++;
	if ((*lineptr)[0] == '(' || (*lineptr)[0] == ')')
		(*lineptr)++;
	else if (((*lineptr)[0] == '|' || (*lineptr)[0] == '&') \
			&& (*lineptr)[1] == (*lineptr)[0])
		(*lineptr) += 2;
	else
		while ((*lineptr)[0] && \
				(*lineptr)[0] != '(' && \
				(*lineptr)[0] != ')' && \
				!(((*lineptr)[0] == '|' || (*lineptr)[0] == '&') \
						&& (*lineptr)[1] == (*lineptr)[0]))
			(*lineptr)++;
	while (ft_isspace((*lineptr)[0]))
		(*lineptr)++;
	return (1);
}

static int	count_log_tokens(char *line)
{
	int	i;

	i = 0;
	while (skip_token(&line))
		i++;
	return (i);
}

int	alloc_log_toks(t_logic_token ***tokens, char *line)
{
	int	tok_amt;
	int	i;

	tok_amt = count_log_tokens(line);
	(*tokens) = ft_calloc(tok_amt + 1, sizeof(t_logic_token *));
	if ((*tokens) == NULL)
		return (0);
	i = 0;
	while (i < tok_amt)
	{
		(*tokens)[i] = malloc(sizeof(t_logic_token));
		if ((*tokens)[i] == NULL)
		{
			while (i > 0)
				free((*tokens)[i-- - 1]);
			free((*tokens));
			(*tokens) = NULL;
			return (0);
		}
		i++;
	}
	(*tokens)[i] = NULL;
	return (tok_amt);
}
