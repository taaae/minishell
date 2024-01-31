/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:48:45 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/31 20:14:26 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include "lexer.h"

char	*join_tokens(t_list *toks);

char	*create_heredoc_file(char *delim)
{
	int		fd;
	char	*pathname;

	pathname = ft_strjoin("/tmp/minishell_heredocs_", delim);
	if (pathname == NULL)
		return (NULL);
	fd = open(pathname, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR | \
						S_IRGRP | S_IWGRP, S_IROTH | S_IWOTH);
	if (fd == -1)
	{
		ft_printf("[%s]\n", strerror(errno));
		ft_printf("Can not create a temp file [%s]\n", pathname);
		free(pathname);
		return (NULL);
	}
	close(fd);
	return (pathname);
}

//TODO
int	read_heredoc_content(char *delim, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (line == NULL)
			continue ;
		line = ft_strtrim(line, "\n");
		if (strcmp(line, delim) == 0)
		{
			free(line);
			return (EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		continue ;
	}
	return (EXIT_SUCCESS);
}

int	read_heredoc_to_file(char *delim, char *storage)
{
	int	fd;
	int	exit_code;

	fd = open(storage, O_WRONLY);
	exit_code = read_heredoc_content(delim, fd);
	close(fd);
	return (exit_code);
}

int	scan_and_write_heredoc(t_token *arrow_tok, t_token *delim_tok)
{
	char	*heredoc_file;

	heredoc_file = create_heredoc_file(delim_tok->token_string);
	if (heredoc_file == NULL)
		return (EXIT_FAILURE);
	if (read_heredoc_to_file(delim_tok->token_string, heredoc_file)
		!= EXIT_SUCCESS)
	{
		arrow_tok->type = TOK_ERROR;
		free(heredoc_file);
		return (EXIT_FAILURE);
	}
	arrow_tok->type = TOK_READ_FROM_FILE_SYM;
	free(arrow_tok->token_string);
	arrow_tok->token_string = ft_strdup("<");
	arrow_tok->token_len = 1;
	delim_tok->type = TOK_WORD;
	free(delim_tok->token_string);
	delim_tok->token_string = heredoc_file;
	delim_tok->token_len = ft_strlen(heredoc_file);
	return (EXIT_SUCCESS);
}

int	check_heredoc_delim_chars(char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == '/' || *delim == '`')
			return (0);
		delim++;
	}
	return (1);
}

int	check_heredoc_delimiter(t_list *toks)
{
	t_token	*cur_tok;
	t_token	*next_tok;

	cur_tok = toks->content;
	if (toks->next != NULL)
		next_tok = toks->next->content;
	else
		return (0);
	if (toks->next == NULL || (\
			next_tok->type != TOK_WORD && \
			next_tok->type != TOK_WORD_IN_QUOTES && \
			next_tok->type != TOK_WORD_IN_DQUOTES && \
			next_tok->type != TOK_VAR))
	{
		cur_tok->type = TOK_ERROR;
		return (0);
	}
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

	if (!check_heredoc_delimiter(toks))
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
		cur_tok = (t_token *)(toks->content);
		if (cur_tok->type == TOK_HEREDOC_SYM)
			if (replace_one_heredoc(toks) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		toks = toks->next;
	}
	return (EXIT_SUCCESS);
}

char	*read_heredocs(char *line)
{
	t_list	*toks;
	char	*res_line;

	if (line[0] == '\0')
		return (ft_strdup(""));
	toks = line_to_tokens(line);
	if (toks == NULL)
		return (NULL);
	if (replace_heredocs(toks) == EXIT_FAILURE)
	{
		ft_lstclear(&toks, del_token);
		return (NULL);
	}
	res_line = join_tokens(toks);
	free(line);
	return (res_line);
}
