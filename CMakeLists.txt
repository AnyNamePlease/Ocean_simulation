cmake_minimum_required(VERSION 3.14)
project(OceanSimulation)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)


include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/utils
)


add_executable(ocean_simulation
    src/main_ocean.cpp
    src/ocean.cpp
    src/entity.cpp
    src/algae.cpp
    src/herbivoreFish.cpp
    src/predatorFish.cpp
    src/sand.cpp
)


target_link_libraries(ocean_simulation PRIVATE Threads::Threads)

# Опционально: если используешь SFML или ncurses — добавь сюда
# Например:
# find_package(sfml 2.5 COMPONENTS graphics window system REQUIRED)
# target_link_libraries(ocean_simulation PRIVATE sfml::graphics sfml::window sfml::system)