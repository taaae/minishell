/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:57:24 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/18 17:35:53 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minunit.h"
#include <stdbool.h>
#include <string.h>
#include "libft.h"
#include "builtins.h"
#include "lexer.h"
#include "environment.h"

void test_setup(void)
{
    /* Nothing */ //
}

void test_teardown(void)
{
	/* Nothing */
}


MU_TEST(test_builtin_pwd)
{
	mu_assert_int_eq(FT_SUCCESS, builtin_pwd());
}

MU_TEST(test_builtin_env)
{
	char *envp[] = {"PATH=/usr/local/bin:/usr/bin", "COLORTERM=truecolor", NULL};
	ft_initenv(envp);
	char *empty_argv[] = {NULL};
	ft_printf("\nbuiltin_env test:\n");
	builtin_env(empty_argv);
	empty_argv[0] = "abc";
	builtin_env(empty_argv);
	empty_argv[0] = NULL;
	ft_unsetenv("PATH");
	ft_unsetenv("COLORTERM");
	builtin_env(empty_argv);
	free(get_environ());
}

MU_TEST(test_builtin_unset)
{
	char *envp[] = {"PATH=/usr/local/bin:/usr/bin", "COLORTERM=truecolor", "USER=root", NULL};
	ft_initenv(envp);
	char *empty_argv[] = {NULL};
	ft_printf("\n\n\nbuiltin_unset test:\n");
	char *unset_argv[] = {"nonexisting", "er=ror", NULL};
	mu_assert_int_eq(1, builtin_unset(unset_argv));
	builtin_env(empty_argv);
	unset_argv[0] = "PATH";
	unset_argv[1] = "USER";
	ft_printf("\n");
	mu_assert_int_eq(0, builtin_unset(unset_argv));
	builtin_env(empty_argv);
	unset_argv[0] = "";
	mu_assert_int_eq(1, builtin_unset(unset_argv));
	unset_argv[0] = "COLORTERM";
	builtin_unset(unset_argv);
	free(get_environ());
}

MU_TEST(test_builtin_export)
{
	char *envp[] = {"PATH=/usr/local/bin:/usr/bin", "COLORTERM=truecolor", "USER=root", NULL};
	ft_initenv(envp);
	char *empty_argv[] = {NULL};
	ft_printf("\n\n\nbuiltin_export test:\n");
	char *argv[] = {"aaa=bbb", "ccc", NULL};
	mu_assert_int_eq(0, builtin_export(argv));
	builtin_env(empty_argv);
	argv[0] = "PATH";
	argv[1] = "COLORTERM";
	builtin_unset(argv);
	ft_printf("\n");
	builtin_env(empty_argv);
	argv[0] = "USER=grot";
	argv[1] = "";
	mu_assert_int_eq(1, builtin_export(argv));
	ft_printf("\n");
	builtin_env(empty_argv);
}

MU_TEST(test_env_error_messages)
{
	ft_printf("\n\ntest env error messages:\n");
	ft_printf("for unset:\n");
	char *argv[] = {" ", "", "a=b", "=2", "=", " a", "2a", "_", "?^@", NULL};
	builtin_unset(argv);
	ft_printf("\nfor export:\n");
	char *argv2[] = {" ", "", "2a=b", " a=b", " b", "_a=b=c", " _a", "?^", NULL};
	builtin_export(argv2);
	char *empty_argv[] = {NULL};
	builtin_env(empty_argv);
}

MU_TEST(test_token_string_utils)
{
	char *s;
#if 0

| || < << > >> & &&

#endif
	s = ft_strdup("|");
	mu_assert_int_eq(1, get_next_tok_len(s));
	free(s);
	s = ft_strdup("||");
	mu_assert_int_eq(2, get_next_tok_len(s));
	free(s);
	s = ft_strdup("<");
	mu_assert_int_eq(1, get_next_tok_len(s));
	free(s);
	s = ft_strdup("<<");
	mu_assert_int_eq(2, get_next_tok_len(s));
	free(s);
	s = ft_strdup(">");
	mu_assert_int_eq(1, get_next_tok_len(s));
	free(s);
	s = ft_strdup(">>");
	mu_assert_int_eq(2, get_next_tok_len(s));
	free(s);
	s = ft_strdup("&");
	mu_assert_int_eq(1, get_next_tok_len(s));
	free(s);
	s = ft_strdup("&&");
	mu_assert_int_eq(2, get_next_tok_len(s));
	free(s);
		
}

MU_TEST_SUITE(test_suite) 
{
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_builtin_echo);
	MU_RUN_TEST(test_builtin_pwd);
	MU_RUN_TEST(test_token_string_utils);
	MU_RUN_TEST(test_environment);
	MU_RUN_TEST(test_builtin_env);
	MU_RUN_TEST(test_builtin_unset);
	MU_RUN_TEST(test_builtin_export);
	MU_RUN_TEST(test_env_error_messages);
}

int main()
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
