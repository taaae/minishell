//
// Created by Timofei Rusanov on 1/23/24.
//
#include <stdio.h>
#include "parser.h"

int main()
{
    char *s[] = {
            "echo a && echo b",
            "echo a || echo b",
    };
    for (int i = 0; s[i] != NULL; i++) {
        printf("input: %s ; result: %s\n", s[i], parse_check(logic_split(s[i])));
    }
}
