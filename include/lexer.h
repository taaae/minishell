/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:15:35 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/11 18:24:11 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type {
	ERROR = 0,
	WORD,
	WORD_IN_QUOTES,
	WORD_IN_DQUOTES,
	READ_FROM_FILE_SYM,
	WRITE_TO_FILE_SYM,
	APPEND_TO_FILE_SYM,
	HEREDOC_SYM,
	PIPE_SYM,
	AND_SYM,
	OR_SYM,
	OPEN_PARENTH,
	CLOSE_PARTNTH	
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