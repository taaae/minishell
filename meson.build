project('minishell_test', 'c', default_options: ['warning_level=2', 'b_sanitize=address'])

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

executable('minishell',
           sources: [src, 'src/minishell.c'],
           include_directories: inc,
           dependencies: dep,
)

