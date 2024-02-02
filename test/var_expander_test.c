#include "unity.h"
#include "libft.h"
#include "parser.h"
#include "environment.h"
#include <string.h>
#include <stdio.h>

void setUp(void) {
    char *envp[] = {"var1=abc", "var2=42", "empty_var=", NULL};
    ft_initenv(envp);
}

void tearDown(void) {
    free(get_environ());
}

void test_basic_expand(void) {
    char *str = strdup("test$var1$var2");
    expand_vars(&str);
    TEST_ASSERT_EQUAL_STRING("testabc42", str);
    free(str);
    str = strdup("$var2$var2");
    expand_vars(&str);
    TEST_ASSERT_EQUAL_STRING("4242", str);
    free(str);
}

void test_no_var_expand(void) {
    char *str = strdup("no_vars");
    expand_vars(&str);
    TEST_ASSERT_EQUAL_STRING("no_vars", str);
    free(str);
}

void test_dollar_expand(void) {
    char *str = strdup("$");
    expand_vars(&str);
    TEST_ASSERT_EQUAL_STRING("$", str);
    free(str);
    str = strdup("test$$");
    expand_vars(&str);
    TEST_ASSERT_EQUAL_STRING("test$$", str);
    free(str);
}

void test_empty_and_non_existing_var_expand(void) {
    char *str = strdup("test$empty_var$empty_var");
    expand_vars(&str);
    TEST_ASSERT_EQUAL_STRING("test", str);
    free(str);
    str = strdup("test$non_existing_var");
    expand_vars(&str);
    TEST_ASSERT_EQUAL_STRING("test", str);
    free(str);
}
