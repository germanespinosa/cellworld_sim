#pragma once
#include <cell_world.h>
#include <cell_world_sim/static_data.h>

namespace cell_world::sim {
        struct Prey_state : cell_world::Agent_internal_state {

        };
        struct Prey : cell_world::Stateful_agent<Prey_state> {
            explicit Prey (const Static_data &);
            cell_world::Move get_move(const Model_public_state &) override;
            cell_world::Agent_status_code update_state(const cell_world::Model_public_state &) override;
            const Cell &start_episode() override;
            const Static_data &data;
            static cell_world::Agent_base &create(const Static_data &);
            static std::vector<Prey> preys;
        };
    }