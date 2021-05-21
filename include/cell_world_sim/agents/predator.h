#pragma once
#include <cell_world.h>
#include <cell_world_sim/static_data.h>

namespace cell_world::sim {
        struct Predator_state : Agent_internal_state {

        };
        struct Predator : Stateful_agent<Predator_state> {
            explicit Predator (const Static_data &, const Cell &);
            Move get_move(const Model_public_state &) override;
            Agent_status_code update_state(const Model_public_state &) override;
            const Cell &start_episode() override;
            const Static_data &data;
            static Agent_base &create(const Static_data &, const Cell &);
            static std::vector<Predator> predators;
            int prey_index;
            const Cell &start;
        };
    }