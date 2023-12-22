#include "unity.h"
#include "libft.h"
#include "environment.h"
#include "builtins.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_environment_core(void) {
  char *to_free;
  char *envp[] = {"PATH=/usr/local/bin:/usr/bin", "COLORTERM=truecolor", NULL};
  ft_initenv(envp);
  TEST_ASSERT_EQUAL_STRING("/usr/local/bin:/usr/bin", to_free = ft_getenv("PATH"));
  free(to_free);
  TEST_ASSERT_EQUAL_STRING("truecolor", to_free = ft_getenv("COLORTERM"));
  free(to_free);
  TEST_ASSERT_EQUAL(NULL, ft_getenv("missing"));
  ft_setenv("newvar", "newval");
  TEST_ASSERT_EQUAL_STRING("newval", to_free = ft_getenv("newvar"));
  free(to_free);
  ft_unsetenv("COLORTERM");
  TEST_ASSERT_EQUAL(NULL, ft_getenv("COLORTERM"));
  TEST_ASSERT_EQUAL(-1, ft_setenv("a=b", "c"));
  TEST_ASSERT_EQUAL(NULL, ft_getenv("a=b"));
  char **environ = get_environ();
  int i = 0;
  for (; environ[i] != NULL; i++) {}
  TEST_ASSERT_EQUAL(2, i);
  TEST_ASSERT_EQUAL(0, ft_unsetenv("missign"));
  TEST_ASSERT_EQUAL(-1, ft_unsetenv("inva=lid"));
  TEST_ASSERT_EQUAL(-1, ft_unsetenv(""));
  ft_unsetenv("PATH");
  ft_unsetenv("newvar");
  ft_setenv("abc", "val=with=equal");
  TEST_ASSERT_EQUAL_STRING("val=with=equal", to_free = ft_getenv("abc"));
  free(to_free);
  ft_unsetenv("abc");
  TEST_ASSERT_EQUAL(get_environ()[0], NULL);
  free(get_environ());
}

void test_builtin_env(void) {
  char *envp[] = {"PATH=/usr/local/bin:/usr/bin", "COLORTERM=truecolor", NULL};
  ft_initenv(envp);
  char *empty_argv[] = {NULL, NULL};
  empty_argv[1] = "argc_0";
  ft_printf("\nbuiltin_env test:\n");
  builtin_env(1, empty_argv);
  empty_argv[1] = "abc";
  builtin_env(1, empty_argv);
  empty_argv[1] = NULL;
  ft_unsetenv("PATH");
  ft_unsetenv("COLORTERM");
  builtin_env(1, empty_argv);
  free(get_environ());
}

void test_builtin_unset(void) {
  char *envp[] = {"PATH=/usr/local/bin:/usr/bin", "COLORTERM=truecolor", "USER=root", NULL};
  ft_initenv(envp);
  char *empty_argv[] = {NULL};
  ft_printf("\n\n\nbuiltin_unset test:\n");
  char *unset_argv[] = {"argv[0]", "nonexisting", "er=ror", NULL};
  TEST_ASSERT_EQUAL(1, builtin_unset(1, unset_argv));
  builtin_env(1, empty_argv);
  unset_argv[1] = "PATH";
  unset_argv[2] = "USER";
  ft_printf("\n");
  TEST_ASSERT_EQUAL(0, builtin_unset(1, unset_argv));
  builtin_env(1, empty_argv);
  unset_argv[1] = "";
  TEST_ASSERT_EQUAL(1, builtin_unset(1, unset_argv));
  TEST_ASSERT_EQUAL(1, builtin_unset(1, unset_argv));
  unset_argv[1] = "COLORTERM";
  builtin_unset(1, unset_argv);
  free(get_environ());
}

void test_builtin_export(void) {
  char *envp[] = {"PATH=/usr/local/bin:/usr/bin", "COLORTERM=truecolor", "USER=root", NULL};
  ft_initenv(envp);
  char *empty_argv[] = {NULL, NULL};
  ft_printf("\n\n\nbuiltin_export test:\n");
  char *argv[] = {"argv[0]", "aaa=bbb", "ccc", NULL};
  TEST_ASSERT_EQUAL(0, builtin_export(1, argv));
  builtin_env(1, empty_argv);
  argv[1] = "PATH";
  argv[2] = "COLORTERM";
  builtin_unset(1, argv);
  ft_printf("\n");
  builtin_env(1, empty_argv);
  argv[1] = "USER=grot";
  argv[2] = "";
  TEST_ASSERT_EQUAL(1, builtin_export(1, argv));
  ft_printf("\n");
  builtin_env(1, empty_argv);
}

void test_env_error_messages(void) {
  ft_printf("\n\ntest env error messages:\n");
  ft_printf("for unset:\n");
  char *argv[] = {"argv[0]", " ", "", "a=b", "=2", "=", " a", "2a", "_", "?^@", NULL};
  builtin_unset(1, argv);
  ft_printf("\nfor export:\n");
  char *argv2[] = {"argv[0]", " ", "", "2a=b", " a=b", " b", "_a=b=c", " _a", "?^", NULL};
  builtin_export(1, argv2);
  char *empty_argv[] = {NULL};
  builtin_env(1, empty_argv);
}
