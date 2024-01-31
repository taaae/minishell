/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:48:45 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/31 17:32:27 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// // 0. Функция-checker, которая идёт по списку и проверяет,
// // 	что после каждого хердока есь слово которе можно юзать ка кделимитер
// // 	Если нет, то в функции уровнем выше мы выводим ошибку:
// // 	bash: syntax error near unexpected
// //gi	token `TOKEN_TYPE (if null, then "newline")'  '
// // 1. функция(Засунуть её прямо в ридер), которая идет и если видит хердок то
// // 	смотрит на следующую штуку, раскавычивает, если надо
// // 	Читает хередок во временный файл
// // 	Записывает в текущий токен чтение с файла 
// // 	Записывает в некст токен название хередок созданного файла
// // 2. Функция, которая склеивает токены через пробел strjoin-ом
// // Check how would my program tokenize  "cat <<    $%&&ls"

#include <fcntl.h>
#include "lexer.h"

// //If file exists, need to remove all of the content from it
// char	*create_heredoc_file(char *delim)
// {
// 	int		fd;
// 	char	*pathname;

// 	pathname = ft_strjoin("/var/tmp/minishell_heredocs/", delim);
// 	if (pathname == NULL)
// 		return (NULL);
// 	fd = open(pathname, O_CREAT);
// 	if (fd == -1)
// 	{
// 		free(pathname);
// 		return (NULL);
// 	}
// 	close(fd);
// 	return (pathname);
// }

// //TODO
// int	read_heredoc_content(char *delim, int fd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline(">");
// 		if (line == NULL)
// 			continue ;
// 		if (line[0] == '\0')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		line = ft_strtrim(line, "\n");
// 		if (strcmp(line, delim))
// 		{
// 			free(line);
// 			return (EXIT_SUCCESS);
// 		}
// 		ft_putstr_fd(line, fd);
// 		ft_putchar_fd("\n", fd);
// 		free(line);
// 		continue ;
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	read_heredoc_to_file(char *delim, char *storage)
// {
// 	int	fd;
// 	int	exit_code;

// 	fd = open(storage, O_WRONLY);
// 	exit_code = read_heredoc_content(delim, fd);
// 	close(fd);
// 	return (exit_code);
// }

// int	scan_and_write_heredoc(t_token *arrow_tok, t_token *delim_tok)
// {
// 	char	*heredoc_file;

// 	heredoc_file = create_heredoc_file(delim_tok->token_string);
// 	if (read_heredoc_to_file(delim_tok->token_string, heredoc_file)
// 		!= EXIT_SUCCESS)
// 	{
// 		arrow_tok->type = TOK_ERROR;
// 		free(heredoc_file);
// 		return (EXIT_FAILURE);
// 	}
// 	arrow_tok->type = TOK_READ_FROM_FILE_SYM;
// 	delim_tok->type = TOK_WORD;
// 	delim_tok->token_string = heredoc_file;
// 	return (EXIT_SUCCESS);
// }

// int	check_heredoc_delim_chars(char *delim)
// {
// 	while (*delim != '\0')
// 	{
// 		if (*delim == '/')
// 			return (0);
// 	}
// 	return (1);
// }

// void	expand_var_heredoc_delim(t_token *tok)
// {
// 	//Write this function later !11
// 	return ;
// }

// int	check_heredoc_delimiter(t_list *toks)
// {
// 	t_token	*cur_tok;
// 	t_token	*next_tok;

// 	cur_tok = toks->content;
// 	if (toks->next != NULL)
// 		cur_tok = toks->next->content;
// 	if (toks->next == NULL || (\
// 			next_tok->type != TOK_WORD && \
// 			next_tok->type != TOK_WORD_IN_QUOTES && \
// 			next_tok->type != TOK_WORD_IN_DQUOTES && \
// 			next_tok->type != TOK_VAR))
// 	{
// 		cur_tok->type = TOK_ERROR;
// 		return (0);
// 	}
// 	if (next_tok->type == TOK_VAR)
// 		expand_var_heredoc_delim(next_tok);
// 	if (!check_heredoc_delim_chars(next_tok->token_string))
// 	{
// 		cur_tok->type = TOK_ERROR;
// 		return (0);
// 	}
// 	return (1);
// }

// int	replace_one_heredoc(t_list *toks)
// {
// 	t_token	*cur_tok;
// 	t_token	*next_tok;

// 	if (!check_heredoc_delimiter)
// 		return (EXIT_FAILURE);
// 	cur_tok = toks->content;
// 	next_tok = toks->next->content;
// 	return (scan_and_write_heredoc(cur_tok, next_tok));
// }

// int	replace_heredocs(t_list *toks)
// {
// 	t_token	*cur_tok;

// 	while (toks != NULL)
// 	{
// 		cur_tok = (t_token *)toks->content;
// 		if (cur_tok->type == TOK_HEREDOC_SYM)
// 			if (replace_one_heredoc(toks) == EXIT_FAILURE)
// 				return (EXIT_FAILURE);
// 		toks = toks->next;
// 	}
// 	return (EXIT_SUCCESS);
// }

char	*read_heredocs(char *line)
{
	t_list	*toks;
	char	*res_line;

	return (line);
	// toks = line_to_tokens(line);
	// replace_heredocs(toks);
	// res_line = join_tokens(toks);
	// free(line);
	// return (res_line);
}

// char	*join_tokens(t_list *toks)
// {
// 	char	*res_line;
// 	int		res_len;
// 	t_lst	toks_save;
// 	int		i;

// 	res_len = get_toklist_len(toks);
// 	res_line = ft_calloc(res_len + 1, sizeof(char));
// 	if (res_line == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (toks)
// 	{
// 		//copy content
// 		//i += content_length
// 		toks = toks->next;
// 	}
// 	ft_lstclear(&toks, NULL);
// }
