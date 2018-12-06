create_project(tp3front EXECUTABLE main.c runner.c container_generator.c)
set(CMAKE_C_FLAGS_RELEASE "-O3")
include_project(tp3front COMMON)
include_raw_project(tp3front fifth)