project(
    'basen',
    'cpp',
    version: '1.1.1',
    default_options: {
        'cpp_std': 'c++20',
        'cpp_args': '-Wall -Wextra -Werror -Wno-unused-result',
    },
    license: 'LGPL-3.0-only',
    license_files: 'LICENSE',
    meson_version: '>=1.10.0',
)

configure_file(
    input: 'config.hpp.in',
    output: 'config.hpp',
    configuration: {'ver_str': meson.project_version()},
)

include = include_directories('.', 'include')

subdir('include')
subdir('src')

basen_dep = declare_dependency(
    link_with: libbasen,
    include_directories: include,
)

if get_option('buildtype') == 'debug'
  subdir('test')
endif

subdir('tools')
