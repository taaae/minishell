/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:57:24 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/18 13:19:34 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minunit.h"
#include <stdbool.h>
#include <string.h>
#include "libft.h"
#include "builtins.h"
#include "lexer.h"

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
	char **ss;
	ss = calloc(3, sizeof(char*));
	ss[0] = strdup("ARG1");
	ss[1] = strdup("ARG2");
	ss[2] = NULL;

	printf("builtins.pwd() tests:\n");
	printf("argv = NULL:\n");
	mu_assert_int_eq(FT_ERROR, builtin_pwd(NULL));

	printf("argv is not an empty string array\n");
	mu_assert_int_eq(1, builtin_pwd(ss));

	free(ss[0]);
	ss[0] = NULL;
	printf("argv is empty\n");
	mu_assert_int_eq(FT_SUCCESS, builtin_pwd(ss));
	free(ss[1]);
	free(ss[2]);
	free(ss);
	
}

MU_TEST(test_builtin_echo)
{
	char **ss;
	ss = calloc(3, sizeof(char*));
	ss[0] = strdup("ARG1");
	ss[1] = strdup("ARG2");
	ss[2] = NULL;

	printf("builtins.echo() tests:\n");
	printf("array,true:\n");
	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, true));
	printf("array,false:\n");
	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, false));

	free(ss[0]);
	ss[0] = NULL;
	printf("empty array, true:\n");
	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, true));
	printf("empty array, false:\n");
	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, false));

	printf("NULL, true:\n");
	mu_assert_int_eq(FT_ERROR, builtin_echo(NULL, true));
	printf("NULL, false:\n");
	mu_assert_int_eq(FT_ERROR, builtin_echo(NULL, false));

	ss[0] = strdup("");
	printf("empty string as 1st arg, true:\n");
	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, true));
	printf("empty string as 1st arg, false:\n");
	mu_assert_int_eq(FT_SUCCESS, builtin_echo(ss, false));
	free(ss[0]);
	free(ss[1]);
	free(ss[2]);
	free(ss);
	
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
}

int main()
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
