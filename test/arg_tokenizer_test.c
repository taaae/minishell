#include "parser.h"

void check(char *str)
{
    ft_printf("%s:   ", str);
    print_token_args(tokenize_arg(str));
}

int main()
{
    check("abc");
    check("abc'def'");
    check("echo$a   'ddd dd'  \"asdasd\"\" '\"");
    check("\"'''''\"'word'");
}