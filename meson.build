project('minishell_test', 'c', default_options: ['warning_level=2'])

cc = meson.get_compiler('c')
libft_dep = cc.find_library('ft', dirs: meson.current_source_dir() + '/libft/')
readline_dep = cc.find_library('readline')

unity_subproject = subproject('unity')
unity_dependency = unity_subproject.get_variable('unity_dep')
unity_gen_runner = unity_subproject.get_variable('gen_test_runner')

dep = [readline_dep, libft_dep, unity_dependency]

c = run_command('glob.sh')
src = c.stdout().strip().split('\n')

inc_dirs = ['include', 'libft']
inc = include_directories(inc_dirs)

# copy-paste these lines, replace 'minishell_test' and 'example_test.c' and 'test/example_test.c'
executable('example_test',
           sources: [src, unity_gen_runner.process('test' / 'example_test.c'), 'test/example_test.c'],
           include_directories: inc,
           dependencies: dep,
)

executable('environment_test',
           sources: [src, unity_gen_runner.process('test' / 'environment_test.c'), 'test/environment_test.c'],
           include_directories: inc,
           dependencies: dep,
)

executable('lexer_test',
           sources: [src, unity_gen_runner.process('test' / 'lexer_test.c'), 'test/lexer_test.c'],
           include_directories: inc,
           dependencies: dep,
)