// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   minishell.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/02/02 17:35:16 by lporoshi          #+#    #+#             */
// /*   Updated: 2024/02/02 17:45:29 by lporoshi         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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

 int execute(char *line)
 {
     t_logic_token	**logic_tokens;
     char           *logic_parse_err;

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
     return (exec_logic(logic_tokens));
 }

 int	main(int argc, char **argv, char **envp)
 {
 	char			*line;

     (void) argc;
     (void) argv;
     ft_initenv(envp); // TODO: free
     init_signal_handlers();
 	while (1)
 	{
 		line = get_line();
 		if (line == NULL)
 			return (0);
 		execute(line);
 		free(line);
 	}
 }
