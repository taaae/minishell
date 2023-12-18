# minishell

🏆FOrmer DaSh ЧamipOns🏆 (☭ ͜ʖ ☭)

## Testing
[Meson built system](https://mesonbuild.com/)
and [Unity testing framework](https://github.com/ThrowTheSwitch/Unity/tree/master) 
are used for testing

Configuring tests:
```bash
make -C libft && make -C libft clean
meson setup build
```

Running test (in built directory):
```bash
meson compile
```
Creating tests:
- Create test file in test directory (use [example_test.c](test/example_test.c) as a reference)
- Check comment in [meson.build](meson.build)
