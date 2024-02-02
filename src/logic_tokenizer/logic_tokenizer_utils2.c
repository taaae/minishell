/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_tokenizer_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:50:38 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/23 17:36:14 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "logic_tokenizer.h"

static int	skip_to_script_end(char **s)
{
	int	in_q;
	int	len;

	in_q = 0;
	len = 0;
	while (1)
	{
		if ((*s)[len] == '\0' || (*s)[len] == '(' \
			|| (*s)[len] == ')' || \
			((*s)[len] == '|' && (*s)[len + 1] == '|') || \
			((*s)[len] == '&' && (*s)[len + 1] == '&'))
			break ;
		if (!in_q && ((*s)[len] == '\'' || (*s)[len] == '"'))
		{
			in_q = (*s)[len++];
			while ((*s)[len] != in_q)
				len++;
			in_q = 0;
		}
		len++;
	}
	return (len);
}

static char	*get_script(char **s)
{
	char	*res;
	int		len;

	len = skip_to_script_end(s);
	res = ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strncpy(res, *s, len);
	res = ft_strtrim(res, "\n\r\t\v\f ");
	*s += ft_strlen(res);
	return (res);
}

static int	read_logic_operator(t_logic_token *token, char **lineptr)
{
	token->strrepr = NULL;
	if ((*lineptr)[0] == '(')
	{
		token->type = OPEN_PAR;
		(*lineptr)++;
		return (1);
	}
	else if ((*lineptr)[0] == ')')
	{
		token->type = CLOS_PAR;
		(*lineptr)++;
		return (1);
	}
	else if ((*lineptr)[0] == '|')
	{
		token->type = OR_SYM;
		(*lineptr) += 2;
		return (2);
	}
	else
	{
		token->type = AND_SYM;
		(*lineptr) += 2;
		return (2);
	}
}

static int	read_tok(t_logic_token *token, char **lineptr)
{
	while (ft_isspace((*lineptr)[0]))
		(*lineptr)++;
	if ((*lineptr)[0] == '(' || \
		(*lineptr)[0] == ')' || \
		(((*lineptr)[0] == '|' || (*lineptr)[0] == '&') && \
			(*lineptr)[0] == (*lineptr)[1]))
		return (read_logic_operator(token, lineptr));
	else if ((*lineptr)[0] != '\0')
	{
		token->type = SCRIPT_STR;
		token->strrepr = get_script(lineptr);
		return (1);
	}
	else
		return (0);
}

void	fill_log_toks(t_logic_token **tokens, int tok_amt, char *line)
{
	int	i;

	i = 0;
	while (i < tok_amt)
	{
		if (!read_tok(tokens[i], &line))
		{
			tokens[i] = NULL;
			break ;
		}
		i++;
	}
	return ;
}
