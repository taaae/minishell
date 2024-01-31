/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:53:26 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/31 19:40:51 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lexer.h"

char	*alloc_toklist_to_str_mem(t_list *toks)
{
	char	*res_mem;
	int		res_len;

	res_len = 0;
	res_mem = NULL;
	if (toks == NULL)
		return (NULL);
	while (toks)
	{
		res_len += ((t_token *)(toks->content))->token_len + 1;
		toks = toks->next;
	}
	res_mem = ft_calloc(res_len + 1, sizeof(char));
	return (res_mem);
}

char	*join_tokens(t_list *toks)
{
	char	*res_line;
	t_lst	*toks_save;
	int		i;

	res_line = alloc_toklist_to_str_mem(toks);
	if (res_line == NULL)
		return (NULL);
	i = 0;
	toks_save = toks;
	while (toks)
	{
		ft_strncpy(res_line + i, ((t_token *)(toks->content))->token_string, \
					((t_token *)(toks->content))->token_len);
		i += ((t_token *)(toks->content))->token_len;
		res_line[i++] = ' ';
		toks = toks->next;
	}
	res_line = ft_strtrim(res_line, " \t");
	ft_lstclear(&toks_save, del_token);
	return (res_line);
}
