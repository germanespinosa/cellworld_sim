#pragma once
#include <cell_world.h>
#include <cell_world_sim.h>
namespace cell_world::sim{
    struct Predator_predictor : cell_world::Stateless_agent{
        Predator_predictor(const Static_data &);
        cell_world::Move get_move(const Model_public_state &) override;
        cell_world::Agent_status_code update_state(const cell_world::Model_public_state &) override;
        const Cell &start_episode() override;
        const Static_data &data;
        int prey_index;
        Cell start;
    };
}