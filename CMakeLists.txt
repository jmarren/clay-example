cmake_minimum_required(VERSION 3.27)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create symlink to compile_commands.json for IDE to pick it up
execute_process(
COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
)

include(FetchContent)


# Download SDL3
FetchContent_Declare(
	SDL
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-3.4.2
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)
message(STATUS "Using SDL via FetchContent")
FetchContent_MakeAvailable(SDL)
set_property(DIRECTORY "${sdl_SOURCE_DIR}" PROPERTY EXCLUDE_FROM_ALL TRUE)

# Download SDL_ttf
FetchContent_Declare(
	SDL_ttf
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
	GIT_TAG release-3.2.2
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)
message(STATUS "Using SDL_ttf via FetchContent")
FetchContent_MakeAvailable(SDL_ttf)
set_property(DIRECTORY "${sdl_ttf_SOURCE_DIR}" PROPERTY EXCLUDE_FROM_ALL TRUE)


# Download SDL_image
FetchContent_Declare(
	SDL_image
	GIT_REPOSITORY "https://github.com/libsdl-org/SDL_image.git"
	GIT_TAG release-3.4.0
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)
message(STATUS "Using SDL_image via FetchContent")
FetchContent_MakeAvailable(SDL_image)
set_property(DIRECTORY "${SDL_image_SOURCE_DIR}" PROPERTY EXCLUDE_FROM_ALL TRUE)


add_library(clay)

add_subdirectory(vendored/clay)

target_link_libraries(
	clay
	PRIVATE
	SDL3::SDL3
	SDL3_ttf::SDL3_ttf
	SDL3_image::SDL3_image
)


project(main)

add_executable(main main.c layout.c layout.h)

target_include_directories(
	main
	PRIVATE
	vendored
)

target_link_libraries(
    main 
    PUBLIC
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    clay
    # SDL2::SDL2main
    # SDL2::SDL2-static
    # SDL2_ttf::SDL2_ttf-static
    # SDL2_image::SDL2_image-static
)


