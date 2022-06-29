project(mathlib)

add_library(mathlib SHARED
    vec.cpp
)

add_library(mathlib::library ALIAS mathlib)

target_include_directories(mathlib
PUBLIC
${PROJECT_SOURCE_DIR}
)