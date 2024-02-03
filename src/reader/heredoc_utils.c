/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:53:26 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/03 17:06:17 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "lexer.h"

char	*alloc_toklist_to_str_mem(t_list *toks)
{
	char	*res_mem;
	int		res_len;

	res_len = 0;
	res_mem = NULL;
	if (toks == NULL)
		return (NULL);
	while (toks)
	{
		res_len += ((t_token *)(toks->content))->token_len + 1;
		toks = toks->next;
	}
	res_mem = ft_calloc(res_len + 1, sizeof(char));
	return (res_mem);
}

char	*join_tokens(t_list *toks)
{
	char	*res_line;
	t_lst	*toks_save;
	int		i;

	res_line = alloc_toklist_to_str_mem(toks);
	if (res_line == NULL)
		return (NULL);
	i = 0;
	toks_save = toks;
	while (toks)
	{
		ft_strncpy(res_line + i, ((t_token *)(toks->content))->token_string, \
					((t_token *)(toks->content))->token_len);
		i += ((t_token *)(toks->content))->token_len;
		res_line[i++] = ' ';
		toks = toks->next;
	}
	res_line = ft_strtrim(res_line, " \t");
	ft_lstclear(&toks_save, del_token);
	return (res_line);
}

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
