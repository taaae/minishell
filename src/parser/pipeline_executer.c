/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:03:15 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 17:52:44 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "environment.h"
#include "expansions.h"
#include <fcntl.h>
#include "exec_find.h"

static int  pipe_num(const t_pipeline_token *pipeline)
{
	int res = 0;

	while (pipeline->type != PIPELINE_EOF)
	{
		res += (pipeline->type == PIPE);
		pipeline++;
	}
	return (res);
}

char	**expand_arg(char *arg)
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

char	**add_arg(char **argv, char *arg)
{
	int		n;
	int		m;
	char	**new;
	char	**expanded;

	expanded = expand_arg(arg);
	n = 0;
	new = argv;
	while (*new != NULL)
	{
		new++;
		n++;
	}
	m = 0;
	new = expanded;
	while (*new != NULL)
	{
		new++;
		m++;
	}
	new = ft_calloc(n + m + 1, sizeof(char *));
	n = 0;
	while (argv[n] != NULL)
	{
		new[n] = argv[n];
		n++;
	}
	m = 0;
	while (expanded[m] != NULL)
	{
		new[n + m] = expanded[m];
		m++;
	}
	free(argv);
	free(expanded);
	return (new);
}

int	handle_redirection(const t_pipeline_token *pipeline)
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
	else if (pipeline->content[0] == '>' && pipeline->content[1] == '\0')
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
	pipeline++;
	return (0);
}

int exec_command(t_pipeline_token *pipeline)
{
	int		code;
	char	**argv;

	argv = ft_calloc(1, sizeof(char *));
	while (pipeline->type != PIPELINE_EOF && pipeline->type != PIPE)
	{
		if (pipeline->type == REDIRECTION)
		{
			code = handle_redirection(pipeline);
			if (code == 1)
				exit(code);
			pipeline++;
		}
		else
			argv = add_arg(argv, pipeline->content);
		pipeline++;
	}
    return (launch_executable(argv));
}

int         exec_pipeline(char *command)
{
	t_pipeline_token	*pipeline;
	t_pipeline_token	*pipeline_to_free;
	int					n;
	int					n2;
	int					p[2];
	int					prev_in;
	int					code;
	int					pid;

	pipeline = tokenize_pipeline(command);
	pipeline_to_free = pipeline;
	n = pipe_num(pipeline) + 1;
    if (n == 1) {
        return exec_command(pipeline);
    }
	n2 = n;
	prev_in = STDIN_FILENO;
	while (n--)
	{
		if (n != 0)
			pipe(p);
		pid = fork();
		if (pid == 0) {
			dup2(prev_in, STDIN_FILENO);
			if (prev_in != STDIN_FILENO)
				close(prev_in);
			if (n != 0) {
				dup2(p[1], STDOUT_FILENO);
				close(p[1]);
			}
			exit(exec_command(pipeline));
		}
		if (prev_in != STDIN_FILENO)
			close(prev_in);
		close(p[1]);
		prev_in = p[0];
		while (pipeline->type != PIPELINE_EOF && pipeline->type != PIPE)
			pipeline++;
		pipeline++;
	}
	waitpid(pid, &code, 0);
	while (n2--)
		wait(NULL);
	free_pipeline(pipeline_to_free);
	return (WEXITSTATUS(code));
}
