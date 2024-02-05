/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:58:25 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/05 13:59:25 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static t_arg_token	*get_squoted(char **arg_ptr)
{
	char		*arg;
	int			len;
	t_arg_token	*tok;

	++(*arg_ptr);
	tok = malloc(sizeof(t_arg_token));
	tok->type = SQUOTED;
	arg = *arg_ptr;
	len = 0;
	while (*arg != '\'')
	{
		arg++;
		len++;
	}
	tok->content = ft_substr(*arg_ptr, 0, len);
	*arg_ptr = arg + 1;
	return (tok);
}

static t_arg_token	*get_dquoted(char **arg_ptr)
{
	char		*arg;
	int			len;
	t_arg_token	*tok;

	++(*arg_ptr);
	tok = malloc(sizeof(t_arg_token));
	tok->type = DQUOTED;
	arg = *arg_ptr;
	len = 0;
	while (*arg != '\"')
	{
		arg++;
		len++;
	}
	tok->content = ft_substr(*arg_ptr, 0, len);
	*arg_ptr = arg + 1;
	return (tok);
}

static t_arg_token	*get_normal(char **arg_ptr)
{
	char		*arg;
	int			len;
	t_arg_token	*tok;

	tok = malloc(sizeof(t_arg_token));
	tok->type = NORMAL_ARG;
	arg = *arg_ptr;
	len = 0;
	while (*arg != '\0' && *arg != '"' && *arg != '\'')
	{
		arg++;
		len++;
	}
	tok->content = ft_substr(*arg_ptr, 0, len);
	*arg_ptr = arg;
	return (tok);
}

t_list	*tokenize_arg(char *arg)
{
	t_list	*lst;

	lst = NULL;
	while (*arg != '\0')
	{
		if (*arg == '\'')
			ft_lstadd_back(&lst, ft_lstnew(get_squoted(&arg)));
		else if (*arg == '"')
			ft_lstadd_back(&lst, ft_lstnew(get_dquoted(&arg)));
		else
			ft_lstadd_back(&lst, ft_lstnew(get_normal(&arg)));
	}
	return (lst);
}

static void	print_node(void *content)
{
	t_arg_token	*tok;

	tok = content;
	if (tok->type == SQUOTED)
		ft_printf("SQ: ");
	else if (tok->type == DQUOTED)
		ft_printf("DQ: ");
	else
		ft_printf("N: ");
	ft_printf("%s, ", tok->content);
}

void	print_token_args(t_list *lst)
{
	ft_lstiter(lst, print_node);
	ft_printf("\n");
}
