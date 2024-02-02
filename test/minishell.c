/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:35:16 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/02 20:17:55 by lporoshi         ###   ########.fr       */
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
1. read heredocs -													char	*read_heredocs(char *line)
2. do logic_split - 												t_logic_token	**logic_split(char *line)
3. parse str to pipelines -					 						???		t_list  *tokenize_arg(char *arg)  or idk
4. give "pipelines" to executor function
	one by one (if needed, depending on logical &&/|| results)		expand_vars(char **str_ptr)
5. In the executor:
	5.x Expand stars												char	**expand_stars_string(char *pattern)  "a*.txt" // if no match then the string itself
	5.x Expand variables											expand_vars(char **str_ptr)
	5.x Tokenize the command to decide what							???	t_pipeline_token    *tokenize_pipeline(char *pipeline)
		is a pipe, what is an exec name,
		what is redirect, what is an argument, etc					
	5.x configure file descriptors
		for reading from files and writing to files					???
	5.x Configure pipelines											???
	5.x Execute this thing											???
*/
int	main(void)
{
	char			*line;
	t_logic_token		**pipelines;
	t_pipeline_token	*pipeline;

	init_signal_handlers();
	while (1)
	{
		line = get_line();
		ft_printf("Line:\t%s\n", line);
		if (line == NULL)
			return (NULL);
		pipelines = logic_split(line);
		while (*pipelines)
		{
			ft_printf("Pipelines:\t%s|\n", (*pipelines)->strrepr);
			pipeline = tokenize_pipeline((*pipelines)->strrepr);
			while (pipeline->content != NULL)
			{
				ft_printf("\tpipeline part: %s\n", pipeline->content);
				pipeline++;
			}
			pipelines++;
		}
		ft_printf("\n");
		free(line);
	}
}
