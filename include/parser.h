#ifndef MINISHELL_PARSER_H
#define MINISHELL_PARSER_H

#include "logic_tokenizer.h"

const char  *logic_parse_check(t_logic_token **token);
int         exec_logic(t_logic_token **token);
const char  *pipeline_parse_check(const char *command);
int         exec_pipeline(const char *command);

#endif
