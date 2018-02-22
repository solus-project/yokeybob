boot_adjust_sources = [
    'main.c',
]

# Just let us get stuff tested first.
boot_adjust = executable(
    'yb-boot-adjust',
    sources: boot_adjust_sources,
    include_directories: config_h_dir,
    install: true,
    install_dir: path_sbindir,
    dependencies: [
        link_libyokeybob,
    ],
)
