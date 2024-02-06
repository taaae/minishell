/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:35:16 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 14:00:41 by lporoshi         ###   ########.fr       */
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

void	execute(char *line)
{
	t_logic_token		**pipelines;
	t_pipeline_token	*pipeline;

	pipelines = logic_split(line);
	while (*pipelines)
	{
		pipeline = tokenize_pipeline((*pipelines)->strrepr);
		while (pipeline->type != PIPELINE_EOF)
		{
			pipeline++;
		}
		pipelines++;
	}
	free(line);
	return ;
}

int	main(void)
{
	char				*line;
	t_logic_token		**pipelines;
	t_pipeline_token	*pipeline;

	init_parent_signals();
	while (1)
	{
		line = get_line();
		//execute(line);
		ft_printf("Line:\t%s\n", line);
		pipelines = logic_split(line);
		while (*pipelines)
		{
			ft_printf("Pipelines:\t%s|\n", (*pipelines)->strrepr);
			pipeline = tokenize_pipeline((*pipelines)->strrepr);
			while (pipeline->type != PIPELINE_EOF)
			{
				if (pipeline->type == ARG)
					ft_printf("\tpipeline part: %s\n", pipeline->content);
				else if (pipeline->type == REDIRECTION)
					ft_printf("\tpipeline part: %s\n", "REDIR");
				else if (pipeline->type == PIPE)
					ft_printf("\tpipeline part: %s\n", "PIPE");
				pipeline++;
			}
			pipelines++;
		}
		ft_printf("\n");
		free(line);
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:10:06 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 13:43:00 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtins.h"
// #include "config.h"
// #include "environment.h"
// #include "exec_find.h"
// #include "expansions.h"
// #include "lexer.h"
// #include "logic_tokenizer.h"
// #include "minishell.h"
// #include "reader.h"
// #include "signals.h"
// #include "libft.h"
// #include "parser.h"

// int	execute(char *line)
// {
// 	t_logic_token	**logic_tokens;
// 	char			*logic_parse_err;

// 	logic_tokens = logic_split(line); // TODO: free it
// 	logic_parse_err = logic_parse_check(logic_tokens);
// 	if (logic_parse_err != NULL)
// 	{
// 		write(STDERR_FILENO, logic_parse_err, ft_strlen(logic_parse_err));
// 		write(STDERR_FILENO, "\n", 1);
// 		free(logic_parse_err);
// 		// free logic tokens
// 		return (258);
// 	}
// 	return (exec_logic(logic_tokens));
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*line;

// 	(void)line;
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	logic_split("abcdefg | dsf | ds | d7 && dsfd sf|| fdsdf << dsfd < sdf < dsf > dsf >> dsfsdf >> dsf > dsf && asdf || (fsdf && dsfs)");
// 	// (void) argc;
// 	// (void) argv;
// 	// ft_initenv(envp); // TODO: free
// 	// init_parent_signals();
// 	// while (1)
// 	// {
// 	// 	line = get_line();
// 	// 	if (line == NULL)
// 	// 		return (0);
// 	// 	execute(line);
// 	// 	free(line);
// 	// }
// }
