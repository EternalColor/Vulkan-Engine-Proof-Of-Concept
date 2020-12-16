add_custom_command(
    COMMAND glslangValidator -V *.vert -o ../build/vert.spv && glslangValidator -V *.frag -o ../build/frag.spv
    OUTPUT shader_compiling_and_moving
    COMMENT "Compiling shaders..."
)

add_custom_target(run ALL
    DEPENDS shader_compiling_and_moving
)