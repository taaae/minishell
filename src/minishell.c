/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:10:06 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 16:07:47 by lporoshi         ###   ########.fr       */
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

int	execute(char *line)
{
	t_logic_token	**logic_tokens;
	char			*logic_parse_err;
	int				code;

	logic_tokens = logic_split(line); // TODO: free it
	logic_parse_err = logic_parse_check(logic_tokens);
	if (logic_parse_err != NULL)
	{
		write(STDERR_FILENO, logic_parse_err, ft_strlen(logic_parse_err));
		write(STDERR_FILENO, "\n", 1);
		free(logic_parse_err);
		// free logic tokens
		return (258);
	}
	code = exec_logic(logic_tokens);
	ptr_arr_free_complex((void ***)&logic_tokens, del_logic_token);
	ft_terminate_env();
	return (code);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void) argc;
	(void) argv;
	ft_initenv(envp); // TODO: free
	init_parent_signals();
	while (1)
	{
		line = get_line();
		if (line == NULL)
			return (0);
		execute(line);
		free(line);
	}
}
