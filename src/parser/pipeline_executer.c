#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "environment.h"

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

char    **expand_arg(char *arg)
{
    // TODO
    // tokenize by normal, double quotes, quotes.
    // expand vars
    // expand wildcards
    // go through the string, split by space if not in quotes/dquotes
    // merge quoted with everything else
    char **expanded;

    expanded = ft_calloc(2, sizeof(char *));
    expanded[0] = arg;
    return (expanded);
}

char    **add_arg(char **argv, char *arg)
{
    int n;
    int m;
    char    **new;
    char    **expanded;

    expanded = expand_arg(arg);
    n = 0;
    new = argv;
    while (*new != NULL)
    {
        new++;
        n++;
    }
    m = 0;
    new = expanded;
    while (*new != NULL)
    {
        new++;
        m++;
    }
    new = ft_calloc(n + m + 1, sizeof(char *));
    n = 0;
    while (argv[n] != NULL)
    {
        new[n] = argv[n];
        n++;
    }
    m = 0;
    while (expanded[m] != NULL)
    {
        new[n + m] = expanded[m];
        m++;
    }
    free(argv);
    free(expanded);
    return (new);
}

#include <stdio.h>
int handle_redirection(const t_pipeline_token *pipeline)
{
    // TODO
    if (pipeline->content[0] == '<')
        fprintf(stderr, "redirecitng from: ");
    else if (pipeline->content[0] == '>' && pipeline->content[1] == '\0')
        fprintf(stderr, "redirecting in: ");
    else if (pipeline->content[0] == '>' && pipeline->content[1] == '>')
        fprintf(stderr, "appending to: ");
    pipeline++;
    fprintf(stderr, "%s\n", pipeline->content);
    return (0);
}

#include <stdio.h>
#include <unistd.h>
void exec_command(t_pipeline_token *pipeline)
{
    int     code;
    char    **argv;

    argv = ft_calloc(1, sizeof(char *));
    while (pipeline->type != PIPELINE_EOF && pipeline->type != PIPE)
    {
        if (pipeline->type == REDIRECTION)
        {
            code = handle_redirection(pipeline); // expand everything here and output error if fail code probably 1 or 0
            if (code == 1)
            {
//                free_argv(argv);
                exit(code);
            }
            pipeline++;
        }
        else
            argv = add_arg(argv, pipeline->content);
        pipeline++;
    }
    system(argv[0]); // fake
//    execve(argv[0], argv + 1, get_environ()); // idk if argv + 1 is good, might need to reallocate to size 1 less. also need to execute the actual executable, not its name (search PATH and builtins)
    // might need to free more stuff
    exit(127); // error not always "command not found", check errno for possible errors
}

int         exec_pipeline(char *command)
{
    t_pipeline_token    *pipeline;
    t_pipeline_token    *pipeline_to_free;
    int n;
    int n2;
    int p[2];
    int prev_in;
    int code;
    int pid;

    pipeline = tokenize_pipeline(command);
    pipeline_to_free = pipeline;
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
    free_pipeline(pipeline_to_free);
    return (WEXITSTATUS(code));
}
