/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:03:15 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/07 17:15:00 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "exec_find.h"
#include "expansions.h"
#include "libft.h"
#include "parser.h"
#include "signals.h"
#include <fcntl.h>
#include <stdlib.h>

int	print_signal_idenfifier(int code)
{
	// ft_printf("[%d -> sig %d and ex %d, signaled = %d]\n", code, WTERMSIG(code), WEXITSTATUS(code), WIFSIGNALED(code));
	if (WIFSIGNALED(code))
	{
		if (128 + WTERMSIG(code) == 131)
			write(2, "Quit: 3\n", 8);
		// else if (128 + WTERMSIG(code) == 130)
		// 	write(2, "\n", 1);
		return (128 + WTERMSIG(code));
	}
	else
	{
		if (WEXITSTATUS(code) == 131)
			write(2, "Quit: 3\n", 8);
		else if (WEXITSTATUS(code) == 131)
			write(2, "\n", 1);
		return (WEXITSTATUS(code));
	}
}

static int	pipe_num(const t_pipeline_token *pipeline)
{
	int	res;

	res = 0;
	while (pipeline->type != PIPELINE_EOF)
	{
		res += (pipeline->type == PIPE);
		pipeline++;
	}
	return (res);
}

void	exec_in_fork(int prev_in, int p[2], t_pipeline_token *pipeline, int n)
{
	dup2(prev_in, STDIN_FILENO);
	if (prev_in != STDIN_FILENO)
		close(prev_in);
	if (n != 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
	}
	exit(exec_command(pipeline));
}

// returns pid of the last one
int	actually_exec_pipeline(int n, t_pipeline_token *pipeline, int prev_in)
{
	int	p[2];
	int	pid;

	while (n--)
	{
		if (n != 0)
			pipe(p);
		pid = fork();
		if (pid == 0)
		{
			exec_in_fork(prev_in, p, pipeline, n);
		}
		if (prev_in != STDIN_FILENO)
			close(prev_in);
		close(p[1]);
		prev_in = p[0];
		while (pipeline->type != PIPELINE_EOF && pipeline->type != PIPE)
			pipeline++;
		pipeline++;
	}
	return (pid);
}

int	exec_pipeline(char *command)
{
	t_pipeline_token	*pipeline;
	int					n;
	int					prev_in;
	int					code;

	pipeline = tokenize_pipeline(command);
	n = pipe_num(pipeline) + 1;
	if (n == 1)
		code = exec_command(pipeline);
	else
	{
		prev_in = STDIN_FILENO;
		waitpid(actually_exec_pipeline(n, pipeline, prev_in), &code, 0);
		while (n--)
			wait(NULL);
		free_pipeline(pipeline);
	}
	return (print_signal_idenfifier(code));
}
