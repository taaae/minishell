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

// int	main(void)
// {
// 	char			*line;
// 	t_logic_token	**splitted_line;

// 	while (1)
// 	{
// 		line = get_line();
// 		if (line == NULL)
// 			return (NULL);
// 		splitted_line = logic_split(line);
// 		while (*splitted_line)
// 		{
// 			ft_printf("%s///", (*splitted_line)->strrepr);
// 			splitted_line++;
// 		}
// 		free(line);
// 	}
// }
