/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:58:25 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 19:01:03 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

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
