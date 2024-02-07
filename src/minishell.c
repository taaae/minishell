/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:10:06 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/07 15:44:11 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "config.h"
#include "environment.h"
#include "exec_find.h"
#include "expansions.h"
#include "global_code.h"
#include "lexer.h"
#include "libft.h"
#include "logic_tokenizer.h"
#include "parser.h"
#include "reader.h"
#include "signals.h"
#include <signal.h>

int	execute(char *line)
{
	t_logic_token	**logic_tokens;
	char			*logic_parse_err;
	int				code;

	signal(SIGINT, SIG_IGN);
	logic_tokens = logic_split(line);
	logic_parse_err = logic_parse_check(logic_tokens);
	if (logic_parse_err != NULL)
	{
		write(STDERR_FILENO, logic_parse_err, ft_strlen(logic_parse_err));
		write(STDERR_FILENO, "\n", 1);
		free(logic_parse_err);
		return (258);
	}
	code = exec_logic(logic_tokens);
	ptr_arr_free_complex((void ***)&logic_tokens, del_logic_token);
	return (code);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	set_return_code(0);
	ft_initenv(envp);
	while (1)
	{
		init_parent_signals();
		line = get_line();
		if (line == NULL)
			return (0);
		set_return_code(execute(line));
		free(line);
	}
}
