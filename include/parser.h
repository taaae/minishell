#ifndef MINISHELL_PARSER_H
#define MINISHELL_PARSER_H

#include "logic_tokenizer.h"

const char  *logic_parse_check(t_logic_token **token);
int         exec_logic(t_logic_token **token);
const char  *pipeline_parse_check(char *command);
int         exec_pipeline(char *command);

typedef enum e_pipeline_token_type {
    ARG,
    REDIRECTION,
    PIPE,
    PIPELINE_EOF
} t_pipeline_token_type;

typedef struct s_pipeline_token
{
    t_pipeline_token_type type;
    char *content;
} t_pipeline_token;

t_pipeline_token    *tokenize_pipeline(char *pipeline);
void                free_pipeline(t_pipeline_token *pipeline);

#endif
