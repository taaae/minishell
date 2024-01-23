/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:15:35 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/22 20:13:59 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <dirent.h>

# define ONE_SYM_WORDS "()"
# define TWO_SYM_WORDS "|&<>"
# define WORD_CHARS "&|<>()\"\'"
# define CONTROL_CHARS "|"

typedef struct s_command {
	char				*execname;
	char				**argv;
	int					argc;
	int					stdout_substitute;
	int					stdin_substitute;
	struct s_command	*next;
}	t_command;

typedef struct s_pipeline {
	t_command			*commands;
	struct s_pipeline	*next;
}	t_pipeline;

typedef struct s_cmdline {
	t_pipeline			*pipelines;
	struct s_command	*next;
}	t_cmdline;
//^
//int exec_cmdline(t_cmdline line)

typedef enum e_token_type {
	TOK_ERROR = 0,
	TOK_WORD = 1,
	TOK_WORD_IN_QUOTES = 2,
	TOK_WORD_IN_DQUOTES = 3,
	TOK_READ_FROM_FILE_SYM = 4,
	TOK_WRITE_TO_FILE_SYM = 5,
	TOK_APPEND_TO_FILE_SYM = 6,
	TOK_HEREDOC_SYM = 7,
	TOK_PIPE_SYM = 8,
	TOK_AND_SYM = 9,
	TOK_OR_SYM = 10,
	TOK_OPEN_PARENTH = 11,
	TOK_CLOSE_PARENTH = 12,
	TOK_EXPANDED_STAR = 13,
	TOK_VAR = 14,
	TOK_EXPANDED_VAR = 15,
	TOK_EXPANDED_VAR_IN_DQOTES = 16,
}	t_token_type;

typedef struct s_token {
	char			*token_string;
	int				token_len;
	t_token_type	type;
}	t_token;

/**
 * @brief Take a bash command and split it into t_list of t_token tokens
 *
 *
 * @param line
 * @return t_list* 
 */
t_list	*line_to_tokens(char *line);
int		get_next_tok_len(char *line);
void	del_token(void *token);
char	*str_to_tok_str(char **line);
t_token	*tok_str_to_token(char *tok_str);

#endif
