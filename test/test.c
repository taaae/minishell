/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:57:24 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/10 16:01:32 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minunit.h"
#include <stdbool.h>
#include <string.h>
#include "libft.h"
#include "builtins.h"

void test_setup(void)
{
    /* Nothing */
}

void test_teardown(void)
{
	/* Nothing */
}

MU_TEST(test_echo)
{
	char **ss;
	ss = calloc(3, sizeof(char*));
	ss[0] = strdup("ARG1");
	ss[1] = strdup("ARG2");
	ss[2] = NULL;

	printf("builtins.echo() tests:\n");
	printf("array,true:\n");
	mu_assert_int_eq(FT_SUCCESS, echo(ss, true));
	printf("array,false:\n");
	mu_assert_int_eq(FT_SUCCESS, echo(ss, false));

	ss[0] = NULL;
	printf("empty array, true:\n");
	mu_assert_int_eq(FT_SUCCESS, echo(ss, true));
	printf("empty array, false:\n");
	mu_assert_int_eq(FT_SUCCESS, echo(ss, false));

	printf("NULL, true:\n");
	mu_assert_int_eq(FT_ERROR, echo(NULL, true));
	printf("NULL, false:\n");
	mu_assert_int_eq(FT_ERROR, echo(NULL, false));

	ss[0] = strdup("");
	printf("empty string as 1st arg, true:\n");
	mu_assert_int_eq(FT_SUCCESS, echo(ss, true));
	printf("empty string as 1st arg, false:\n");
	mu_assert_int_eq(FT_SUCCESS, echo(ss, false));
	
}

MU_TEST_SUITE(test_suite) 
{
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_echo);
}

int main()
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
