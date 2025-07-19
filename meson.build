project('C+Phys', 'cpp',
        default_options: [ 'cpp_std=c++23', 'warning_level=3' ],
        version: '1.0.0-alpha')

sdl = dependency('sdl3')
json = dependency('jsoncpp')

add_project_dependencies([
    sdl, json
], language: 'cpp')

add_project_arguments([
    '-DAPP_NAME="@0@"'.format(meson.project_name()),
    '-DAPP_VERSION="@0@"'.format(meson.project_version()),
], language: 'cpp')

# Debug mode
if get_option('buildtype').contains('debug')
    add_project_arguments([ '-D__DEBUG' ], language: 'cpp')
endif

sdl_files = files(
    'src/sdl/objects/box.cc',
    'src/sdl/objects/button.cc',
    'src/sdl/obj.cc',
    'src/sdl/sdl.cc',
)

source_files = files(
    'src/main.cc',
) + sdl_files

executable('cphys', source_files,
           include_directories: include_directories('include'),
           build_by_default: true)