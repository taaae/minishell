/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:49:01 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/22 22:12:00 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "logic_tokenizer.h"

int	skip_token(char **lineptr)
{
	if (**lineptr == '\0')
		return (0);
	if ((*lineptr)[0] == '(' || (*lineptr)[0] == ')')
		(*lineptr)++;
	else if (((*lineptr)[0] == '|' || (*lineptr)[0] == '&') \
			&& (*lineptr)[1] == (*lineptr)[0])
		(*lineptr) += 2;
	else
		while ((*lineptr)[0] && (*lineptr)[0] != '(' || (*lineptr)[0] != ')' && \
				!(((*lineptr)[0] == '|' || (*lineptr)[0] == '&') \
						&& (*lineptr)[1] == (*lineptr)[0]))
			(*lineptr)++;
	return (1);
}

int	count_log_tokens(char *line)
{
	int	i;

	i = 0;
	while (skip_token(&line))
		i++;
	return (i);
}

int	alloc_log_toks(t_logic_token **tokens, char *line)
{
	int	tok_amt;
	int	i;

	tok_amt = count_log_tokens(line);
	tokens = ft_calloc(tok_amt + 1, sizeof(t_logic_token *));
	if (tokens == NULL)
		return (NULL);
	i = 0;
	while (i < tok_amt)
	{
		tokens[i] = ft_calloc(1, sizeof(t_logic_token));
		if (tokens[i] == 0)
		{
			while (i > 0)
				free(tokens[i-- - 1]);
			free(tokens);
			tokens = NULL;
			return (0);
		}
		i++;
	}
	return (tok_amt);
}

int	skip_to_script_end(char **s)
{
	int	in_q;
	int	len;

	in_q = 0;
	len = 0;
	while (1)
	{
		if (found_the_end_of_token_or_end_of_line)
			break;
		if (!in_q && **s == '\'' || **s == '"')
		{
			in_q = *((*s)++);
			while (**s != in_q)
				(*s)++;
			in_q = 0;
		}
		(*s)++;
	}
	return (len);
}

char	*get_script(char **s)
{
	char	*res;
	int		len;

	len = skip_to_script_end(s);
	res = ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strncpy(res, *s, len);
	*s += len;
	return (res);
}

int	read_tok(t_logic_token *token, char **lineptr)
{
	if ((*lineptr)[0] == '(')
	{
		token->type = OPEN_PAR;
		(*lineptr)++;
		return (1);
	}
	if ((*lineptr)[0] == ')')
	{
		token->type = CLOS_PAR;
		(*lineptr)++;
		return (1);
	}
	else if ((*lineptr)[0] == '|' && (*lineptr)[1] == '|')
	{
		token->type = OR_SYM;
		(*lineptr) += 2;
		return (2);
	}
	else if ((*lineptr)[0] == '&' && (*lineptr)[1] == '&')
	{
		token->type = AND_SYM;
		(*lineptr) += 2;
		return (2);
	}
	else
	{
		token->type = SCRIPT_STR;
		token->strrepr = get_script(lineptr);
	}
	return (1);
}

void	fill_log_toks(t_logic_token **tokens, int tok_amt, char *line)
{
	int	i;

	while (i < tok_amt)
	{
		read_tok(tokens[i], &line);
	}
	return ;
}

int	quotes_are_correct(char *line)
{
	while (1)
	{
		if (*line == '\'')
		{
			line++;
			while (*line && *line != '\'')
				line++;
			if (*line == '\0')
				return (0);
		}
		if (*line == '"')
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

t_logic_token	**logic_split(char *line)
{
	t_logic_token	*tokens;
	int				tok_amt;

	if (!quotes_are_correct(line))
		return (NULL);
	tok_amt = alloc_log_toks(tokens, line);
	if (tokens == NULL)
		return (NULL);
	fill_log_toks(tokens, tok_amt, line);
	return (tokens);
}
