#pragma once
#include <cell_world.h>


namespace cell_world::sim {
    struct Static_data{
        enum Agent_type{
            predator,
            prey
        };
        Static_data(const std::string &);
        const cell_world::World world;
        const cell_world::Cell_group cells;
        const cell_world::Map map;
        const cell_world::Paths paths;
        std::vector<Agent_type> agents;
    };
}