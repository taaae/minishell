project('minishell_test', 'c')

unity_dep = dependency('unity')
readline_dep = dependency('readline')
dep = [unity_dep, readline_dep]

cc = meson.get_compiler('c')
libft = cc.find_library('ft', dirs: meson.current_source_dir() + '/libft/')
dep += libft

c = run_command('glob.sh')
sources = c.stdout().strip().split('\n')

inc_dirs = ['include', 'libft']
include = include_directories(inc_dirs)

executable('minishell_test', sources,
           include_directories: include,
           dependencies: dep,
)
