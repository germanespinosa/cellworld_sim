#pragma once
#include <cell_world.h>
#include <cell_world_sim/static_data.h>


namespace cell_world::sim {
        struct Predator_state : cell_world::Agent_internal_state {

        };
        struct Predator : cell_world::Stateful_agent<Predator_state> {
            explicit Predator (const Static_data &);
            cell_world::Move get_move(const Model_public_state &) override;
            const Cell &start_episode() override;
            const Static_data &data;
            static cell_world::Agent_base &create(const Static_data &);
            static std::vector<Predator> predators;
        };
    }