/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:15:07 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 14:53:30 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "lexer.h"
#include "libft.h"
#include "reader.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int		replace_heredocs(t_list *toks);
char	*join_tokens(t_list *toks);

char	*read_heredocs(char *line)
{
	t_list	*toks;
	char	*res_line;

	if (line[0] == '\0')
	{
		res_line = ft_strdup("");
		free(line);
		return (res_line);
	}
	toks = line_to_tokens(line);
	if (toks == NULL)
	{
		free(line);
		return (NULL);
	}
	if (replace_heredocs(toks) == EXIT_FAILURE)
	{
		ft_lstclear(&toks, del_token);
		free(line);
		return (NULL);
	}
	res_line = join_tokens(toks);
	free(line);
	return (res_line);
}

void	init_reader(void)
{
	using_history();
}

void	close_reader(void)
{
	rl_clear_history();
}

char	*get_line(void)
{
	char	*line;

	while (1)
	{
		line = readline(SHELL_PROMPT);
		if (line == NULL)
			return (NULL);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		line = read_heredocs(line);
		return (line);
	}
}
