//
// Created by Timofei Rusanov on 1/29/24.
//
#include "parser.h"
#include <string.h>
#include <stdio.h>

static char *type_to_content(t_pipeline_token_type type)
{
    switch (type)
    {
        case ARG:
            return strdup("ARG");
        case REDIRECTION:
            return strdup("REDIRECTION");
        case PIPE:
            return strdup("PIPE");
        case PIPELINE_EOF:
            return strdup("EOF");
    }
}

static void print_pipeline_tokens(t_pipeline_token *pipeline)
{
    while (pipeline->type != PIPELINE_EOF)
    {
        printf("type: %s, content: %s\n", type_to_content(pipeline->type), pipeline->content);
        pipeline++;
    }
};

int main()
{
//    print_pipeline_tokens(tokenize_pipeline("ls -l | grep \"pattern\" > > < < out.txt && cat < out.txt"));
    char *line = "abc | \"def'\"| e";
    printf("%s\n%s\n", line, pipeline_parse_check(line));
}
