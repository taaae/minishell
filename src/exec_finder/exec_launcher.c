#include "libft.h"
#include "environment.h"
#include "exec_find.h"
#include "builtins.h"

static int argv_size(char **argv)
{
	int res;

	res = 0;
	while (*argv != NULL)
	{
		argv++;
		res++;
	}
	return (res);
}

static void launch_builtin(char **argv)
{
	int argc;

	argc = argv_size(argv);
	if (ft_strcmp(argv[0], "cd") == 0)
		exit (builtin_cd(argc, argv));
	if (ft_strcmp(argv[0], "echo") == 0)
		exit(builtin_echo(argc, argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		exit(builtin_pwd(argc, argv));
	if (ft_strcmp(argv[0], "env") == 0)
		exit(builtin_env(argc, argv));
	if (ft_strcmp(argv[0], "export") == 0)
		exit(builtin_export(argc, argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		exit(builtin_unset(argc, argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		exit(builtin_exit(argc, argv));
}

/**
 * search launches executable and exits with its return code
 * @param argv - dinamically allocated, argv[0] is executable name
 * @return checks errno if execve fails, 0 if size of argv is 0, otherwise return code of execve
*/
void     launch_executable(char **argv)
{
	char *exec_path;
	if (argv[0] == NULL)
	{
		free(argv);
		exit(0);
	}
	launch_builtin(argv);
	exec_path = expand_exec_name(argv[0]);
	if (exec_path == NULL)
	{
		write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
		write(STDERR_FILENO, argv[0], ft_strlen(argv[0]));
		write(STDERR_FILENO, ": command not found\n", ft_strlen(": command not found\n"));
		exit(127);
	}
	execve(exec_path, argv, get_environ());
	perror("minishell");
	// TODO: some frees?
	exit(126); // idk most likely no permissions, might be something else
}
