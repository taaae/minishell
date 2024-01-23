#include <stddef.h>
#include "parser.h"
#include "logic_tokenizer.h"

const char    *token_error(const t_logic_token *token)
{
    if (token == NULL)
        return "minishell: unexptected empty token";
    if (token->type == OPEN_PAR)
        return "minishell: syntax error near unexpected token `('";
    if (token->type == CLOS_PAR)
        return "minishell: syntax error near unexpected token `)'";
    if (token->type == OR_SYM)
        return "minishell: syntax error near unexpected token `||'";
    if (token->type == AND_SYM)
        return "minishell: syntax error near unexpected token `&&'";
    if (token->type == SCRIPT_STR)
        return "minishell: syntax error near unexpected token script_str";
    return "minishell: unexptected token type";
}

const char    *parse_check_expr(t_logic_token ***token);
const char    *parse_check_term(t_logic_token ***token);

// Expr -> Term{('&&', '||')Term}
// Term -> '(' Expr ')' | script_str
// Pass first element of NULL terminated token array from logic_split func
// Returns NULL on success or stack-allocated string with error description if fail
#include <stdio.h>
const char    *parse_check(t_logic_token **token)
{
    const char    *res;

    res = parse_check_expr(&token);
    if (res != NULL)
        return (res);
    if (*token != NULL)
        return (token_error(*token));
    return (NULL);
}

const char    *parse_check_expr(t_logic_token ***token)
{
    const char    *res;

    res = parse_check_term(token);
    if (res != NULL)
        return (res);
    if (**token == NULL)
        return (NULL);
    if ((**token)->type == AND_SYM || (**token)->type == OR_SYM)
    {
        (*token)++;
        return (parse_check_term(token));
    }
    return (token_error(**token));
}

const char    *parse_check_term(t_logic_token ***token)
{
    const char    *res;

    if (**token == NULL)
        return (token_error(NULL));
    if ((**token)->type == SCRIPT_STR)
    {
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
