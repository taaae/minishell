/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:15:07 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/31 17:31:11 by lporoshi         ###   ########.fr       */
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

char	*read_heredocs(char *line);

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
		add_history(line);
		line = read_heredocs(line);
		return (line);
	}
}
