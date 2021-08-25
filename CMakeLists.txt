cmake_minimum_required( VERSION 3.10 )

set(CMAKE_CXX_STANDARD 20)

project( cellworld_sim
        VERSION 2021.1.0
        DESCRIPTION "Cellworld sim"
        LANGUAGES CXX)

find_package(Cellworld_tools REQUIRED)

set (cellworld_sim_files
        src/cell_world_sim/static_data.cpp
        src/cell_world_sim/simulation.cpp
        src/cell_world_sim/generative_model.cpp
        src/cell_world_sim/belief_state.cpp
        src/cell_world_sim/forward_information_search.cpp
        src/cell_world_sim/agents/prey.cpp
        src/cell_world_sim/agents/prey_predictor.cpp
        src/cell_world_sim/agents/predator.cpp
        src/cell_world_sim/agents/predator_predictor.cpp
        src/main.cpp  )

add_library( cellworld_sim ${cellworld_sim_files})

target_link_libraries ( cellworld_sim ${CELLWORLD_TOOLS_LIBRARIES})

target_include_directories(cellworld_sim
        PUBLIC
        include )

add_executable(simulation src/main.cpp)
target_link_libraries( simulation  cellworld_sim)



###
### TESTS
###
find_package(CatchTests CONFIG QUIET)


###
### SIMULATION INSTALLATION
###

if (CMAKE_BUILD_TYPE MATCHES Release)

    include(GNUInstallDirs)

    install(TARGETS cellworld_sim
            RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})


endif()