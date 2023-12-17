/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:57:24 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/17 17:04:53 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minunit.h"
#include <stdbool.h>
#include <string.h>
#include "libft.h"
#include "builtins.h"
#include "environment.h"

void test_setup(void)
{
    /* Nothing */ //
}

void test_teardown(void)
{
	/* Nothing */
}


// MU_TEST(test_builtin_pwd)
// {
// 	char **ss;
// 	ss = calloc(3, sizeof(char*));
// 	ss[0] = strdup("ARG1");
// 	ss[1] = strdup("ARG2");
// 	ss[2] = NULL;

// 	printf("builtins.pwd() tests:\n");
// 	printf("argv = NULL:\n");
// 	mu_assert_int_eq(FT_ERROR, builtin_pwd(NULL));

// 	printf("argv is not an empty string array\n");
// 	mu_assert_int_eq(1, builtin_pwd(ss));

// 	free(ss[0]);
// 	ss[0] = NULL;
// 	printf("argv is empty\n");
// 	mu_assert_int_eq(FT_SUCCESS, builtin_pwd(ss));
// 	free(ss[1]);
// 	free(ss[2]);
// 	free(ss);
	
// }

// MU_TEST(test_builtin_echo)
// {
// 	char **ss;
// 	ss = calloc(3, sizeof(char*));
// 	ss[0] = strdup("ARG1");
// 	ss[1] = strdup("ARG2");
// 	ss[2] = NULL;

// 	printf("builtins.echo() tests:\n");
// 	printf("array,true:\n");
// 	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, true));
// 	printf("array,false:\n");
// 	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, false));

// 	free(ss[0]);
// 	ss[0] = NULL;
// 	printf("empty array, true:\n");
// 	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, true));
// 	printf("empty array, false:\n");
// 	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, false));

// 	printf("NULL, true:\n");
// 	mu_assert_int_eq(FT_ERROR, builtin_echo(NULL, true));
// 	printf("NULL, false:\n");
// 	mu_assert_int_eq(FT_ERROR, builtin_echo(NULL, false));

// 	ss[0] = strdup("");
// 	printf("empty string as 1st arg, true:\n");
// 	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, true));
// 	printf("empty string as 1st arg, false:\n");
// 	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, false));
// 	free(ss[0]);
// 	free(ss[1]);
// 	free(ss[2]);
// 	free(ss);
// }

MU_TEST(test_environment)
{
	char *to_free;
	char *envp[] = {"PATH=/usr/local/bin:/usr/bin", "COLORTERM=truecolor", NULL};
	ft_initenv(envp);
	mu_assert_string_eq("/usr/local/bin:/usr/bin", to_free = ft_getenv("PATH"));
	free(to_free);
	mu_assert_string_eq("truecolor", to_free = ft_getenv("COLORTERM"));
	free(to_free);
	mu_assert_string_eq(NULL, ft_getenv("missing"));
	ft_setenv("newvar", "newval");
	mu_assert_string_eq("newval", to_free = ft_getenv("newvar"));
	free(to_free);
	ft_unsetenv("COLORTERM");
	mu_assert_string_eq(NULL, ft_getenv("COLORTERM"));
	mu_assert_int_eq(-1, ft_setenv("a=b", "c"));
	mu_assert_string_eq(NULL, ft_getenv("a=b"));
	char **environ = get_environ();
	int i = 0;
	for (; environ[i] != NULL; i++) {}
	mu_assert_int_eq(2, i);
	mu_assert_int_eq(0, ft_unsetenv("missign"));
	mu_assert_int_eq(-1, ft_unsetenv("inva=lid"));
	mu_assert_int_eq(-1, ft_unsetenv(""));
	ft_unsetenv("PATH");
	ft_unsetenv("newvar");
	ft_setenv("abc", "val=with=equal");
	mu_assert_string_eq("val=with=equal", to_free = ft_getenv("abc"));
	free(to_free);
	ft_unsetenv("abc");
	mu_assert(get_environ()[0] == NULL, "environ should be empty now");
	free(get_environ());
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
}

MU_TEST_SUITE(test_suite) 
{
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	// MU_RUN_TEST(test_builtin_echo);
	// MU_RUN_TEST(test_builtin_pwd);
	MU_RUN_TEST(test_environment);
	MU_RUN_TEST(test_builtin_env);
	MU_RUN_TEST(test_builtin_unset);
}

int main()
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
