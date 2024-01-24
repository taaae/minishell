//
// Created by Timofei Rusanov on 1/23/24.
//
#include <stdio.h>
#include "parser.h"

int main()
{
    char *s[] = {
            "echo abc",
            "echo",
            "echo abc && )",
            "&&",
            "echo abc &&",
            "||",
            "()",
            "(echo abc) | echo",
            "",
            "echo aaa && ()",
            "((",
            "echo a && echo b && echo c",
            "(echo a && echo b)",
            "''",
            "'",
            "(echo hello",
            "echo world))",
            "&& echo hello",
            "echo world ||",
            "echo a && || echo b",
            "echo a || && echo b",
            "echo hello && ||",
            "&& && &&",
            "&& echo hello &&",
            "echo (())",
            "echo hello && || && echo world",
            "echo \"Hello",
            "echo 'World",
            "echo hello >",
            "< echo world",
            "echo hello echo world",
            "(echo hello && (echo world || echo!))",
            "(echo inner) && echo outer",
            "echo this && echo that || echo those && echo these",
            "echo 'echo nested'",
            "((echo a && (echo b || (echo c))) && (((echo d))))",
            "((((echo a && echo b)) || ((echo c || echo d))))",
            "echo a && (echo b || (echo c && (echo d))) || (echo e)",
            "((echo a || (echo b)) && echo c) || (((echo d && echo e)))",
            "() && echo a || (()) && echo b",
            "(((((echo a)))) && echo b) || echo c",
            "((||) && echo a) || ((echo b &&))",
            "((echo a || (echo b && echo c)) && ((echo d || echo e)))",
            "(echo a || (echo b && echo c)) && ((echo d || echo e)))",
            "((echo a || (echo b && echo c) && ((echo d || echo e)))",
            "((echo a || (echo b && echo c)) && ((echo d || echo e))",
            "((((echo a && echo b)) || ((echo c || echo d))",
            "((((echo a && echo b)) || ((echo c || echo d)))",
            "echo a && echo b)) || ((echo c || echo d",
            NULL,
    };
    for (int i = 0; s[i] != NULL; i++) {
        printf("input: %s\n result: %s\n\n", s[i], logic_parse_check(logic_split(s[i])));
    }
}
