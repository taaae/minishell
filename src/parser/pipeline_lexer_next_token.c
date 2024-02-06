/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_lexer_next_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:20:49 by trusanov          #+#    #+#             */
/*   Updated: 2024/02/06 18:51:21 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static char	*string_append(char *str, char c)
{
	char	*to_append;
	char	*res;

	to_append = malloc(2);
	to_append[0] = c;
	to_append[1] = '\0';
	res = ft_strjoin(str, to_append);
	free(str);
	free(to_append);
	return (res);
}

t_pipeline_token	handle_symbols(char **str, char *p)
{
	t_pipeline_token	token;

	if (*p == '|')
	{
		token.type = PIPE;
		token.content = NULL;
		*str = p + 1;
		return (token);
	}
	token.type = REDIRECTION;
	if (*p == '<')
	{
		token.content = ft_strdup("<");
		*str = p + 1;
		return (token);
	}
	if (p[0] == '>' && p[1] == '>')
	{
		token.content = ft_strdup(">>");
		*str = p + 2;
		return (token);
	}
	token.content = ft_strdup(">");
	*str = p + 1;
	return (token);
}

t_pipeline_token	next_token(char **str)
{
	char				*p;
	t_pipeline_token	token;
	char				quote_type;

	p = *str;
	if (*p == '|' || *p == '<' || *p == '>')
		return (handle_symbols(str, p));
	token.type = ARG;
	quote_type = '\0';
	token.content = ft_calloc(1, 1);
	while (quote_type != '\0' || (*p != '\0' && !ft_isspace(*p) && *p != '|'
			&& *p != '>' && *p != '<'))
	{
		token.content = string_append(token.content, *p);
		if (*p == quote_type)
			quote_type = '\0';
		else if (*p == '"' && quote_type == '\0')
			quote_type = '"';
		else if (*p == '\'' && quote_type == '\0')
			quote_type = '\'';
		p++;
	}
	*str = p;
	return (token);
}
