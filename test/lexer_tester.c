/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:45:03 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/14 17:44:23 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "config.h"
#include "lexer.h"
#include "libft.h"

#define RED_TERM "\e[1;31m"
#define RESET_TERM "\e[0m"

//Run from root folder:
// cc -g3 -fsanitize=address -Iinclude -Ilibft  -L./libft -lft test/lexer_tester.c src/lexer/*.c && ./a.out 'cat /dev/random | head -c 100 | wc -c'


int	print_list_item_w_token(t_list	*item)
{
	t_token	*t;

	t = (t_token *)item->content;
	// printf("%p %p %p %p\n", item, item->content, item->next, t);
	//ft_printf("[%s]\t\t\t\tlen[%d]type[%d]\n", t->token_string, t->token_len, \
		t->type);
	ft_printf("%s", t->token_string);
	ft_printf(RED_TERM);
	ft_printf("¦", 1);
	ft_printf(RESET_TERM);
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	*l;

	//printf("LINE=[%s]\n", argv[1]);
	l = tokenize(argv[1]);
	while (l && l->content)
	{
		print_list_item_w_token(l);
		l = l->next;
	}
	return (0);
}
