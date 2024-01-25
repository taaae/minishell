/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:48:45 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/25 16:11:50 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
//
0. Функция-checker, которая идёт по списку и проверяет, что после каждого хердока есь слово которе можно юзать ка кделимитер
	Если нет, то в функции уровнем выше мы выводим ошибку  bash: syntax error near unexpected token `TOKEN_TYPE (if null, then "newline")'  '
1. функция(Засунуть её прямо в ридер), которая идет и если видит хердок то
	смотрит на следующую штуку, раскавычивает, если надо
	Читает хередок во временный файл
	Записывает в текущий токен чтение с файла
	Записывает в некст токен название хередок созданного файла
2. Функция, которая склеивает токены через пробел strjoin-ом

Check how would my program tokenize  "cat <<    $%&&ls"
*/

#include <fcntl.h>
#include "lexer.h"

//If file exists, need to remove all of the content from it
char	*create_heredoc_file(char *delim)
{
	int		fd;
	char	*pathname;

	pathname = ft_strjoin("/var/tmp/minishell_heredocs/", delim);
	if (pathname == NULL)
		return (NULL);
	fd = open(pathname, O_CREAT);
	if (fd == -1)
	{
		free(pathname);
		return (NULL);
	}
	close(fd);
	return (pathname);
}

int	scan_and_write_heredoc(t_token *arrow_tok, t_token delim_tok)
{
	//1. Create file for storage function
	//2. Call a function for reading a heredoc
		//1. readline() with '>' prompt (don't update history)
		//2. strcmp(what I read, delim_tok)
		//3. 	If not equal, write a line to the file
		//4. 		Go to step 2
		//5. 	if equal, wrap up the FD and return full path filename
	//3. If return NULL, error. If return a string, then continue
	//4. arrow_tok -> change type to INFILE, tok_str and tok len to match "<"
	//5. delim_tok -> change type to word, tok_str/tok_len to match full path to temp file
	//6. return 1;
}


int	check_heredoc_delim_chars(char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == '/')
			return (0);
	}
	return (1);
}

void	expand_var_heredoc_delim(t_token *tok)
{
	//Write this function later !11
	return ;
}

int	check_heredoc_delimiter(t_list *toks)
{
	t_token	*cur_tok;
	t_token	*next_tok;

	cur_tok = toks->content;
	if (toks->next != NULL)
		cur_tok = toks->next->content;
	if (toks->next == NULL || (\
			next_tok->type != TOK_WORD && \
			next_tok->type != TOK_WORD_IN_QUOTES && \
			next_tok->type != TOK_WORD_IN_DQUOTES && \
			next_tok->type != TOK_VAR))
	{
		cur_tok->type = TOK_ERROR;
		return (0);
	}
	if (next_tok->type == TOK_VAR)
		expand_var_heredoc_delim(next_tok);
	if (!check_heredoc_delim_chars(next_tok->token_string))
	{
		cur_tok->type = TOK_ERROR;
		return (0);
	}
	return (1);
}

int	replace_one_heredoc(t_list *toks)
{
	t_token	*cur_tok;
	t_token	*next_tok;

	if (!check_heredoc_delimiter)
		return (EXIT_FAILURE);
	cur_tok = toks->content;
	next_tok = toks->next->content;
	return (scan_and_write_heredoc(cur_tok, next_tok));
}

int	replace_heredocs(t_list *toks)
{
	t_token	*cur_tok;

	while (toks != NULL)
	{
		cur_tok = (t_token *)toks->content;
		if (cur_tok->type == TOK_HEREDOC_SYM)
			if (replace_one_heredoc(toks) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		toks = toks->next;
	}
	return (EXIT_SUCCESS);
}

char	*read_heredoc(char *line)
{
	t_list	*toks;
	char	*res_line;

	toks = line_to_tokens(line);
	replace_heredocs(toks);
	res_line = join_tokens(toks);
	free(line);
	return (res_line);
}
