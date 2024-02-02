#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

# include "logic_tokenizer.h"
# include "libft.h"

char        *logic_parse_check(t_logic_token **token);
int         exec_logic(t_logic_token **token);
char  *pipeline_parse_check(char *command);
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

typedef enum e_arg_token_type
{
    NORMAL_ARG,
    DQUOTED,
    SQUOTED,
} t_arg_token_type;

typedef struct s_arg_token
{
    t_arg_token_type type;
    char *content;
} t_arg_token;

t_list  *tokenize_arg(char *arg);
void    print_token_args(t_list *lst);
void expand_vars(char **str);

#endif
