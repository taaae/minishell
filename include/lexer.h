/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:15:35 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/19 13:06:37 by lporoshi         ###   ########.fr       */
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
 * @brief Breaks a line into tokens and returns linked list of them
 *
 * @param line
 * @return t_token*
 */
t_list	*tokenize(char *line);
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

int		count_files_in_cur_dir(void);
void	scan_files_in_dir(char ***files, int files_count, \
DIR *d, struct dirent *dir);
char	*str_to_tok_str(char **line);
t_list	*line_to_tokens(char *line);
int		expand_all_vars(t_list **tokens);
int		match_wildcard(char *str, char *pattern);

/**
 * @brief Takes tok list, returns tok list with all stars expanded
 *
 * Every time it finds a token node that has * in its str_repr,
 * it expands it to a token list, and replaces the node with this list.
 * It should be able to expand 1st and last node of the list.
 * If it couldn't resolve expansion of a token (no matches) or an error occurred,
 * it just sets the type of existing token to TOK_ERROR.
 * @param tok_lst
 * @return int
 */
int		expand_all_stars(t_list **tok_lst);
void	del_token(void *token);
t_list	*expanded_star_to_token(char *s);

#endif