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
void exec_command(t_pipeline_token *pipeline);

int main()
{
//    print_pipeline_tokens(tokenize_pipeline("ls -l | grep \"pattern\" > > < < out.txt && cat < out.txt"));
    (exec_command(tokenize_pipeline("abc > file < file2 >>fil3 def")));
}
