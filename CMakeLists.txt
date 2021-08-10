
file(GLOB_RECURSE bead_SRC RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "**.h"
    "**.cpp"
    "**.rc"
    "**.ico"
)

add_library(bead STATIC ${bead_SRC} )

