/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:55:32 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/18 11:38:28 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "lexer.h"

static int	ordered_substrings_match(char *s, char **substrings);
static int	match_wildcard(char *str, char *pattern);
static int	append_expansion_str(char **expansion, char *appendix);
char		*compose_expansion_str(char *pattern, char **candidates);
char		*expand_string(char *pattern);

int	print_tok_list(t_list *tok)
{
	t_token	*t;

	//ft_printf("[");
	while (tok != NULL && tok->content != NULL)
	{
		t = (t_token *)tok->content;
		//ft_printf("\t[%d]\t", t->token_len);
		//ft_printf("\t[%d]\t", t->type);
		ft_printf("%s", t->token_string);
		ft_printf("\033[31m|\e[0m");
		tok = tok->next;
	}
	ft_printf("\n");
	return (FT_SUCCESS);
}

int	main(int argc, char **argv)
{
	char	**res;
	t_list	*toks;

	//printf("[%s]\n", argv[1]);
	toks = line_to_tokens(argv[1]);
	//printf("%p\n", toks);
	print_tok_list(toks);
	return (0);
}

// cc -Iinclude -Ilibft -L./libft -lft -g -fsanitize=address src/lexer/*.c test/test_star_expander.c && ./a.out "**first**2**3rd**" "abyrwalg first time that I got 2 on the exam that was 3rd in the session" "bad string" "" "abc" "first23rd" "first_2_3rd" "first22223rd3rd3rd" "first2" "     first23rd    "
