#include "libft.h"
#include "environment.h"
#include "exec_find.h"
#include "builtins.h"

#define NOT_BUILTIN -42

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

static int launch_builtin(char **argv)
{
	int argc;

	argc = argv_size(argv);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argc, argv));
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argc, argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(argc, argv));
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(argc, argv));
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argc, argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argc, argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argc, argv));
    return (NOT_BUILTIN);
}

/**
 * search launches executable and returns its return code. forks if custom executable, doesnt work if builtn
 * @param argv - dinamically allocated, argv[0] is executable name
 * @return checks errno if execve fails, 0 if size of argv is 0, otherwise return code of execve
*/
int launch_executable(char **argv)
{
	char *exec_path;
    int  code;
    int pid;

	if (argv[0] == NULL)
	{
		free(argv);
		exit(0);
	}
	code = launch_builtin(argv);
    if (code != NOT_BUILTIN) {
        return (code);
    }
    pid = fork();
    if (pid == 0) {
        exec_path = expand_exec_name(argv[0]);
        if (exec_path == NULL) {
            write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
            write(STDERR_FILENO, argv[0], ft_strlen(argv[0]));
            write(STDERR_FILENO, ": command not found\n", ft_strlen(": command not found\n"));
            exit(127);
        }
        execve(exec_path, argv, get_environ());
        perror("minishell");
        exit(126);
    }
    waitpid(pid, &code, 0);
    return WEXITSTATUS(code);
}
