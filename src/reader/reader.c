/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:15:07 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/12 18:58:35 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "libft.h"
#include "reader.h"
#include "config.h"

void	init_reader(void)
{
	using_history();
}

void	close_reader(void)
{
	rl_clear_history();
}

static bool	unclosed_brackets(char *line)
{
	bool	unclosed_quote;
	bool	unclosed_dquote;
	int		unclosed_parenth;

	unclosed_quote = false;
	unclosed_dquote = false;
	unclosed_parenth = 0;
	while (*line)
	{
		if (*line == '\'')
			unclosed_quote = !unclosed_quote;
		else if (*line == '"')
			unclosed_dquote = !unclosed_dquote;
		else if (*line == '(')
			unclosed_parenth += 1;
		else if (*line == ')')
			unclosed_parenth -= 1;
	}
	return (unclosed_quote == true || unclosed_dquote == true \
	|| unclosed_parenth != 0);
}

char	*get_line(void)
{
	char			*line;

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
		if (unclosed_brackets(line) == true)
		{
			free(line);
			ft_putstr_fd("Unclosed quotes or brackets!\n", STDERR_FILENO);
			continue ;
		}
		add_history(line);
		return (line);
	}
}
