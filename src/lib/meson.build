lib_sources = [
    'topology.c',
]

libyokeybob = static_library(
    'yokeybob',
    sources: lib_sources,
    include_directories: config_h_dir,
    install: false,
)

link_libyokeybob = declare_dependency(
    link_with: libyokeybob,
    include_directories: [
        include_directories('.'),
    ],
)
