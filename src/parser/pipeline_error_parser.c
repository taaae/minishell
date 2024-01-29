#include "parser.h"
#include "libft.h"

const char  *pipeline_parse_check(char *line)
{
    t_pipeline_token *pipeline;
    t_pipeline_token *pipeline_to_free;
    char    *res;

    pipeline = tokenize_pipeline(line);
    pipeline_to_free = pipeline;
    while (pipeline->type != PIPELINE_EOF)
    {
        if (pipeline->type == PIPE  && (pipeline[1].type == PIPELINE_EOF || pipeline[1].type == PIPE))
        {
            free_pipeline(pipeline_to_free);
            return (ft_strdup("minishell: syntax error near unexpected token `|'"));
        }
        if (pipeline->type == REDIRECTION && pipeline[1].type == PIPELINE_EOF)
        {
            free_pipeline(pipeline_to_free);
            return (ft_strdup("minishell: syntax error near unexpected token `newline'"));
        }
        if (pipeline->type == REDIRECTION && pipeline[1].type == REDIRECTION)
        {
            res = ft_strjoin("minishell: syntax error near unexpected token: ", pipeline[1].content);
            free_pipeline(pipeline_to_free);
            return (res);
        }
        pipeline++;
    }
    free_pipeline(pipeline_to_free);
    return (NULL);
}
