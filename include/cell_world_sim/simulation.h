#pragma once
#include <cell_world.h>
#include <cell_world_sim/agents.h>
#include <cell_world_sim/static_data.h>


namespace cell_world::sim {
    struct Simulation{
      explicit Simulation(const Static_data &);
      void run();
      cell_world::Model model;
    };
}