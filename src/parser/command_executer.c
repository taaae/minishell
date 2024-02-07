/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:13:24 by trusanov          #+#    #+#             */
/*   Updated: 2024/02/07 15:04:38 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "exec_find.h"
#include "expansions.h"
#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <stdlib.h>

static char	**expand_arg(char *arg)
{
	char	*expanded_str;
	char	**res;

	if (arg[0] == '\'')
	{
		res = ft_calloc(2, sizeof(char *));
		expanded_str = ft_substr(arg, 1, ft_strlen(arg) - 2);
		res[0] = expanded_str;
		return (res);
	}
	if (arg[0] == '"')
	{
		res = ft_calloc(2, sizeof(char *));
		expanded_str = ft_substr(arg, 1, ft_strlen(arg) - 2);
		expand_vars(&expanded_str);
		res[0] = expanded_str;
		return (res);
	}
	expanded_str = ft_strdup(arg);
	expand_vars(&expanded_str);
	expanded_str = expand_stars_string(expanded_str);
	res = ft_split(expanded_str, ' ');
	free(expanded_str);
	return (res);
}

static char	**add_arg(char **argv, char *arg)
{
	int		n;
	int		m;
	char	**new;
	char	**expanded;

	expanded = expand_arg(arg);
	n = 0;
	new = argv;
	while (*(new++) != NULL)
		n++;
	m = 0;
	new = expanded;
	while (*(new++) != NULL)
		m++;
	new = ft_calloc(n + m + 1, sizeof(char *));
	n = 0;
	while (argv[n] != NULL && ++n)
		new[n - 1] = argv[n - 1];
	m = 0;
	while (expanded[m] != NULL && ++m)
		new[n + m - 1] = expanded[m - 1];
	free(argv);
	free(expanded);
	return (new);
}

static int	handle_redirection_in_file(const t_pipeline_token *pipeline)
{
	int	fd;

	if (pipeline->content[0] == '>' && pipeline->content[1] == '\0')
	{
		fd = open(pipeline[1].content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
		{
			perror("minishell");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (pipeline->content[0] == '>' && pipeline->content[1] == '>')
	{
		fd = open(pipeline[1].content, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
		{
			perror("minishell");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

static int	handle_redirection(const t_pipeline_token *pipeline)
{
	int	fd;

	if (pipeline->content[0] == '<')
	{
		fd = open(pipeline[1].content, O_RDONLY);
		if (fd == -1)
		{
			perror("minishell");
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		if (handle_redirection_in_file(pipeline) == 1)
			return (1);
	}
	pipeline++;
	return (0);
}

int	exec_command(t_pipeline_token *pipeline)
{
	int		code;
	char	**argv;
	int		orig_stdin;
	int		orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	argv = ft_calloc(1, sizeof(char *));
	while (pipeline->type != PIPELINE_EOF && pipeline->type != PIPE)
	{
		if (pipeline->type == REDIRECTION)
		{
			code = handle_redirection(pipeline++);
			if (code != 0)
				exit(code);
		}
		else
			argv = add_arg(argv, pipeline->content);
		pipeline++;
	}
	if (argv != NULL && argv[0] !=  NULL)
		code = launch_executable(argv);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	return (code);
}
