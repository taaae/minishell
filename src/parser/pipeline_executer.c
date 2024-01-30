#include <stdlib.h>
#include "parser.h"

static int  pipe_num(const t_pipeline_token *pipeline)
{
    int res = 0;

    while (pipeline->type != PIPELINE_EOF)
    {
        res += (pipeline->type == PIPE);
        pipeline++;
    }
    return (res);
}

#include <stdio.h>
#include <unistd.h>
static void exec_command(const t_pipeline_token *pipeline)
{
    while (pipeline->type != PIPELINE_EOF && pipeline->type != PIPE)
    {
        fprintf(stderr, "%s\n", pipeline->content);
        pipeline++;
    }
    exit(42);
}

int         exec_pipeline(char *command)
{
    t_pipeline_token    *pipeline;
    int n;
    int n2;
    int p[2];
    int prev_in;
    int code;
    int pid;

    pipeline = tokenize_pipeline(command);
    n = pipe_num(pipeline) + 1;
    n2 = n;
    prev_in = STDIN_FILENO;
    while (n--)
    {
        if (n != 0)
            pipe(p);
        pid = fork();
        if (pid == 0) {
            dup2(prev_in, STDIN_FILENO);
            if (prev_in != STDIN_FILENO)
                close(prev_in);
            if (n != 0) {
                dup2(p[1], STDOUT_FILENO);
                close(p[1]);
            }
            exec_command(pipeline);
        }
        close(prev_in);
        close(p[1]);
        prev_in = p[0];
        while (pipeline->type != PIPELINE_EOF && pipeline->type != PIPE)
                pipeline++;
        pipeline++;
    }
    waitpid(pid, &code, 0);
    while (n2--)
        wait(NULL);
    return (WEXITSTATUS(code));
}
