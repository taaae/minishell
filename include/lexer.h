/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:15:35 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/14 17:38:14 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define ONE_SYM_WORDS "()"
# define TWO_SYM_WORDS "|&<>"
# define WORD_CHARS "&|<>()\"\'"
# define CONTROL_CHARS "|"

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
	TOK_CLOSE_PARENTH = 12	
}	t_token_type;

typedef struct s_token {
	char			*token_string;
	int				token_len;
	t_token_type	type;
}	t_token;

/**
 * @brief Breaks a line into tokens and returns linked list of them
 *
 * @param line
 * @return t_token*
 */
t_list	*tokenize(char *line);
void	del_token(void *token);
char	*str_to_tok_str(char **line);
t_token	*tok_str_to_token(char *tok_str);
t_list	*token_to_list_entry(t_token *token);

/**
 * @brief Get the next tok len object
 *
 * Cant possibly get ' ' or '\0'!
 * @param line
 * @return int
 */
int		get_next_tok_len(char *line);
int		parse_double_sym_word(char *line);
int		parse_quotes(char *line);
int		parse_dquotes(char *line);
int		parse_word(char *line);
int		parse_var(char *line);

/**
 * @brief Get the token type object
 *
 * TODO
 * @param tok_str
 * @param tok_len
 * @return int
 */
int		get_token_type(char *tok_str, int tok_len);

#endif