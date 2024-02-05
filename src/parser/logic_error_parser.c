/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_error_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:03:09 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/05 14:05:17 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "parser.h"
#include "logic_tokenizer.h"

static char	*token_error(const t_logic_token *token)
{
	if (token == NULL)
		return (ft_strdup("minishell: unexptected empty token"));
	if (token->type == OPEN_PAR)
		return (ft_strdup("minishell: syntax error near unexpected token `('"));
	if (token->type == CLOS_PAR)
		return (ft_strdup("minishell: syntax error near unexpected token `)'"));
	if (token->type == OR_SYM)
		return (ft_strdup("minishell: syntax error near \
							unexpected token `||'"));
	if (token->type == AND_SYM)
		return (ft_strdup("minishell: syntax error near \
							unexpected token `&&'"));
	if (token->type == SCRIPT_STR)
		return (ft_strjoin("minishell: syntax error near unexpected token: ", \
				token->strrepr));
	return (ft_strdup("minishell: unexptected token type"));
}

static char	*parse_check_expr(t_logic_token ***token);
static char	*parse_check_term(t_logic_token ***token);

// Expr -> Term{('&&', '||')Expr}
// Term -> '(' Expr ')' | pipeline
// Pass first element of NULL terminated token array from logic_split func
// Returns NULL on success or dynamically 
// 		allocated string with error description if fail
char	*logic_parse_check(t_logic_token **token)
{
	char	*res;

	if (token == NULL)
		return (ft_strdup("minishell: unclosed quote"));
	res = parse_check_expr(&token);
	if (res != NULL)
		return (res);
	if (*token != NULL)
		return (token_error(*token));
	return (NULL);
}

static char	*parse_check_expr(t_logic_token ***token)
{
	char	*res;

	res = parse_check_term(token);
	if (res != NULL)
		return (res);
	if (**token == NULL)
		return (NULL);
	if ((**token)->type == AND_SYM || (**token)->type == OR_SYM)
	{
		(*token)++;
		return (parse_check_expr(token));
	}
	return (NULL);
}

static char	*parse_check_term(t_logic_token ***token)
{
	char	*res;

	if (**token == NULL)
		return (token_error(NULL));
	if ((**token)->type == SCRIPT_STR)
	{
		res = pipeline_parse_check((**token)->strrepr);
		if (res != NULL)
			return (res);
		(*token)++;
		return (NULL);
	}
	if ((**token)->type == OPEN_PAR)
	{
		(*token)++;
		res = parse_check_expr(token);
		if (res != NULL)
			return (res);
		if (**token == NULL || (**token)->type != CLOS_PAR)
			return (token_error(**token));
		(*token)++;
		return (NULL);
	}
	return (token_error(**token));
}
