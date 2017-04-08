file(GLOB root_source "*.cc")
file(GLOB_RECURSE source "*.cc")

add_executable(vcs ${root_source} ${source})

target_link_libraries(vcs)
