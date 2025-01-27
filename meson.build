project('four-in-a-row', 'c', 'vala',
    version: '3.33.91'
)

add_global_arguments('-DGETTEXT_PACKAGE="@0@"'.format (meson.project_name()), language: 'c')

# used to install help
gnome = import('gnome')
# used for internationalization
i18n = import('i18n')
# used to run post install script
python3 = import('python3')

application_id = 'org.gnome.Four-in-a-row'

gio_dependency = dependency('gio-2.0', version: '>= 2.40.0')
glib_dependency = dependency('glib-2.0', version: '>= 2.40.0')
gsound_dependency = dependency('gsound', version: '>= 1.0.2')
gtk_dependency = dependency('gtk+-3.0', version: '>= 3.13.2')
rsvg_dependency = dependency('librsvg-2.0', version: '>= 2.32.0')

appstream_util          = find_program('appstream-util',        required: false)
desktop_file_validate   = find_program('desktop-file-validate', required: false)
glib_compile_schema     = find_program('glib-compile-schemas',  required: true) # useful?

datadir = join_paths(get_option('prefix'), get_option('datadir'), meson.project_name())

conf = configuration_data ()
conf.set_quoted('VERSION', meson.project_version())
conf.set_quoted('GETTEXT_PACKAGE', meson.project_name())
conf.set_quoted('SOUND_DIRECTORY', join_paths(datadir, 'sounds'))
conf.set_quoted('LOCALEDIR', join_paths(get_option('prefix'), get_option('localedir')))
conf.set_quoted('DATA_DIRECTORY', datadir)

configure_file(output: 'config.h', configuration: conf)
config_h_dir = include_directories('.')


subdir('data')
subdir('help')
subdir('po')
subdir('src')

meson.add_install_script(python3.find_python().path(), join_paths(meson.source_root(), 
                                                                  'build-aux', 
                                                                  'meson_post_install.py'))
