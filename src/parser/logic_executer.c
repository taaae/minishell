/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_executer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:03:13 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 15:33:12 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "parser.h"
#include "logic_tokenizer.h"

#define SUCCESS 0

static t_logic_token	**skip_term(t_logic_token **token);
static t_logic_token	**skip_expr(t_logic_token **token);

void	del_logic_token(void *tok_vptr)
{
	t_logic_token *tok_ptr;

	tok_ptr = (t_logic_token *)tok_vptr;
	free(tok_ptr->strrepr);
	free(tok_ptr);
	return ;
}

// before executing this function execute
//	logic_parse_check to make sure the tokenstream is valid
int	exec_logic(t_logic_token **token)
{
	int					code;
	t_logic_tok_type	op;

	if ((*token)->type == OPEN_PAR)
		code = exec_logic(token + 1);
	else
		code = exec_pipeline((*token)->strrepr);
	token = skip_term(token);
	while (*token && (*token)->type != CLOS_PAR)
	{
		op = (*token)->type;
		token++;
		if (op == OR_SYM ^ code == SUCCESS)
		{
			if ((*token)->type == OPEN_PAR)
				code = exec_logic(token + 1);
			else
				code = exec_pipeline((*token)->strrepr);
		}
		token = skip_term(token);
	}
	return (code);
}

static t_logic_token	**skip_term(t_logic_token **token)
{
	if ((*token)->type == OPEN_PAR)
	{
		token++;
		token = skip_expr(token);
	}
	return (token + 1);
}

static t_logic_token	**skip_expr(t_logic_token **token)
{
	while (*token && (*token)->type != CLOS_PAR)
		token = skip_term(token);
	return (token);
}
