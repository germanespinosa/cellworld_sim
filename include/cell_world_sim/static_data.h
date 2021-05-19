#pragma once
#include <cell_world.h>


namespace cell_world::sim {
        struct Static_data{
            Static_data(const cell_world::Cell_group &);
            cell_world::Cell_group cells;
            cell_world::Map map;
        };
    }