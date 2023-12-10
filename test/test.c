/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:57:24 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/10 14:32:52 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minunit.h"

void test_setup(void)
{
    /* Nothing */
}

void test_teardown(void)
{
	/* Nothing */
}

MU_TEST_SUITE(test_suite) 
{
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
}

int main()
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
