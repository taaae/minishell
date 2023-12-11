/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:15:35 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/11 18:41:14 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type {
	TOK_ERROR = 0,
	TOK_WORD,
	TOK_WORD_IN_QUOTES,
	TOK_WORD_IN_DQUOTES,
	TOK_READ_FROM_FILE_SYM,
	TOK_WRITE_TO_FILE_SYM,
	TOK_APPEND_TO_FILE_SYM,
	TOK_HEREDOC_SYM,
	TOK_PIPE_SYM,
	TOK_AND_SYM,
	TOK_OR_SYM,
	TOK_OPEN_PARENTH,
	TOK_CLOSE_PARTNTH	
}	t_token_type;

typedef struct s_token {
	char			*token_string;
	int				token_len;
	t_token_type	type;
	t_token			*next;
}	t_token;

/**
 * @brief Breaks a line into tokens and returns linked list of them
 * 
 * @param line 
 * @return t_token* 
 */
t_token	*tokenize(char *line);

#endif