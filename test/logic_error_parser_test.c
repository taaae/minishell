//
// Created by Timofei Rusanov on 1/23/24.
//
#include <stdio.h>
#include "parser.h"

int main()
{
    char *s[] = {
            "echo abc && )",
            NULL,
    };
    t_logic_token **a = logic_split("echo abc && )");
    printf("%p\n", a);
    for (int i = 0; s[i] != NULL; i++) {
        printf("input: %s ; result: %s\n", s[i], parse_check(logic_split(s[i])));
    }
}
