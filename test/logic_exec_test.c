#include <stdio.h>
#include "parser.h"

int main() {
    char *s[] = {
            "A",
            "A && B",
            "A || B",
            "A && B && C && D && E",
            "A || B || C || D || E",
            "A && B || C && D && E || F || G",
            "A || B || C || D && E && F && G",
            "(A && B)",
            "A && (B || C) && D",
            "A || (B && (C || D)) && E",
            "(((((echo a)))) && echo b) || echo c",
            "((echo a || (echo b)) && echo c) || (((echo d && echo e)))",
            "echo a && (echo b || (echo c && (echo d))) || (echo e)",
            "((((echo a && echo b)) || ((echo c || echo d))))",
            "((echo a && (echo b || (echo c))) && (((echo d))))",
            "echo 'echo nested'",
            "echo this && echo that || echo those && echo these",
            NULL
    };
    for (int i = 0; s[i] != NULL; i++) {
        printf("input: %s\n result: %i\n\n", s[i], exec_logic(logic_split(s[i])));
    }
}