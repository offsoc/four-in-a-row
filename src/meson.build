four_in_a_row_tests = executable('four-in-a-row-tests', 
    [
        'ai.vala',
        'test-ai.vala'
    ],
    dependencies: [
        gio_dependency,
        glib_dependency
    ]
)
test('four-in-a-row-tests', 
    four_in_a_row_tests,
    timeout: 180)



sources = files(
    'ai.vala',
    'four-in-a-row.vala',
    'game-board-view.vala',
    'game-board.vala',
    'games-controls-list.vala',
    'prefs-box.vala',
    'prefs.vala',
    'scorebox.vala',
    'theme.vala',
    'vapi/config.vapi'
)

executable(
    meson.project_name(),
    sources,
    dependencies: [
        glib_dependency,
        gsound_dependency,
        gtk_dependency,
        rsvg_dependency
    ],
    c_args: [
        '-include', 'config.h'
    ],
    vala_args: [
        '--target-glib', '2.44',
        '--vapidir', join_paths(meson.current_source_dir(), 'vapi')
    ],
    install: true,
    install_dir: get_option('bindir')
)
