#include "parser.h"
#include "libft.h"

void    free_pipeline(t_pipeline_token *pipeline)
{
    t_pipeline_token *ptr;

    ptr = pipeline;
    while (ptr->type != PIPELINE_EOF) {
        free(ptr->content);
        ptr++;
    }
    free(pipeline);
}

static void pipeline_append(t_pipeline_token **arr, t_pipeline_token new)
{
    size_t i;
    t_pipeline_token *res;

    i = 0;
    while ((*arr)[i].type != PIPELINE_EOF)
        i++;
    res = (t_pipeline_token  *)malloc((i + 2) * sizeof(t_pipeline_token));
    i = 0;
    while ((*arr)[i].type != PIPELINE_EOF)
    {
        res[i] = (*arr)[i];
        i++;
    }
    res[i].type = new.type;
    res[i].content = new.content;
    res[i + 1] = (*arr)[i];
    free(*arr);
    *arr = res;
}

static char *string_append(char *str, char c)
{
    char *to_append;
    char *res;

    to_append = malloc(2);
    to_append[0] = c;
    to_append[1] = '\0';
    res = ft_strjoin(str, to_append);
    free(str);
    free(to_append);
    return (res);
}

t_pipeline_token next_token(char **str)
{
    char *p;
    t_pipeline_token token;
    char *content;
    char quote_type;

    p = *str;
    if (*p == '|')
    {
        token.type = PIPE;
        token.content = NULL;
        *str = p + 1;
        return (token);
    }
    if (*p == '<')
    {
        token.type = REDIRECTION;
        token.content = ft_strdup("<");
        *str = p + 1;
        return (token);
    }
    if (p[0] == '>' && p[1] == '>')
    {
        token.type = REDIRECTION;
        token.content = ft_strdup(">>");
        *str = p + 2;
        return (token);
    }
    if (*p == '>')
    {
        token.type = REDIRECTION;
        token.content = ft_strdup(">");
        *str = p + 1;
        return (token);
    }
    token.type = ARG;
    quote_type = '\0';
    content = ft_calloc(1, 1);
    while (quote_type != '\0' || (*p != '\0' && !ft_isspace(*p) && *p != '|' && *p != '>' && *p != '<'))
    {
        content = string_append(content, *p);
        if (*p == quote_type)
            quote_type = '\0';
        else if (*p == '"' && quote_type == '\0')
            quote_type = '"';
        else if (*p == '\'' && quote_type == '\0')
            quote_type = '\'';
        p++;
    }
    token.content = content;
    *str = p;
    return (token);
}

t_pipeline_token    *tokenize_pipeline(char *pipeline)
{
    t_pipeline_token *res;
    t_pipeline_token next;

    res = malloc(sizeof(t_pipeline_token));
    res[0].type = PIPELINE_EOF;
    res[0].content = NULL;
    while (*pipeline != '\0')
    {
        while (ft_isspace(*pipeline))
            pipeline++;
        if (*pipeline == '\0')
            break;
        next = next_token(&pipeline);
        pipeline_append(&res, next);
    }
    return (res);
}
