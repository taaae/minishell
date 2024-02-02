/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:35:16 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/02 19:23:39 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "config.h"
#include "environment.h"
#include "exec_find.h"
#include "expansions.h"
#include "lexer.h"
#include "logic_tokenizer.h"
#include "minishell.h"
#include "reader.h"
#include "signals.h"
#include "libft.h"
#include "parser.h"

/*
1. read heredocs
2. do logic_split
3. parse logic_split to whatever structure 
4. give "pipelines" to executor function one by one (if needed, depending on logical &&/|| results)
5. In the executor:
	5.x Expand stars
	5.x Expand variables
	5.x Tokenize the command to decide what is a pipe, what is an exec name, what is redirect, what is an argument, etc
	5.x configure file descriptors for reading from files and writing to files
	5.x Configure pipelines
	5.x Execute this shit
*/
int	main(void)
{
	char			*line;
	t_logic_token	**splitted_line;

	init_signal_handlers();
	while (1)
	{
		line = get_line();
		if (line == NULL)
			return (NULL);
		splitted_line = logic_split(line);
		while (*splitted_line)
		{
			ft_printf("%s///", (*splitted_line)->strrepr);
			splitted_line++;
		}
		free(line);
	}
}
