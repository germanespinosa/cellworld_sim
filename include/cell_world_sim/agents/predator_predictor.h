#pragma once
#include <cell_world.h>
#include <cell_world_sim.h>
#include <cell_world_sim/agents/predictor_state.h>

namespace cell_world::sim{

    struct Predator_predictor : Stateful_agent<Predictor_state>{
        explicit Predator_predictor(const Static_data &);
        Move get_move(const Model_public_state &) override;
        Agent_status_code update_state(const Model_public_state &) override;
        const Cell &start_episode() override;
        static Agent_base &create(const Static_data &);
        const Static_data &data;
        int prey_index;
        Cell start;
        static std::vector<Predator_predictor> predators;
    };
}