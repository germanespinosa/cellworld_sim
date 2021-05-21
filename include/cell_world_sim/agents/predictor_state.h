#pragma once
#include <cell_world.h>

namespace cell_world::sim {
    struct Predictor_state : Agent_internal_state {
        Cell destination;
    };
}