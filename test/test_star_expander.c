/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_star_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:55:33 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/18 15:10:48 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	ordered_substrings_match(char *s, char **substrings);
static int	match_wildcard(char *str, char *pattern);
static int	append_expansion_str(char **expansion, char *appendix);
char		*compose_expansion_str(char *pattern, char **candidates);
char		*expand_star_string(char *pattern);

int	main(int argc, char **argv)
{
	char	**res;

	//printf("[%s]\n", compose_expansion_str(argv[1], argv + 2));
	printf("[%s]\n", expand_string(argv[1]));
	return (0);
}

// cc -Iinclude -Ilibft -L./libft -lft -g -fsanitize=address src/lexer/*.c test/test_star_expander.c && ./a.out "**first**2**3rd**" "abyrwalg first time that I got 2 on the exam that was 3rd in the session" "bad string" "" "abc" "first23rd" "first_2_3rd" "first22223rd3rd3rd" "first2" "     first23rd    "
