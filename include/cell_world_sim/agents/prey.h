#pragma once
#include <cell_world.h>
#include <cell_world_sim/static_data.h>
#include <cell_world_sim/agents/predator_predictor.h>
#include <cell_world_sim/generative_model.h>
namespace cell_world::sim {
        struct Prey_state : Agent_internal_state {
        };
         struct Prey : cell_world::Stateful_agent<Prey_state> {
            explicit Prey (const Static_data &, const Cell &);
            cell_world::Move get_move(const Model_public_state &) override;
            cell_world::Agent_status_code update_state(const cell_world::Model_public_state &) override;
            const Cell &start_episode() override;
            const Static_data &data;
            static cell_world::Agent_base &create(const Static_data &, const Cell &);
            static std::vector<Prey> preys;
            const Cell &start;
            const Cell &goal;
            Model generative_model;
            int predator_index;
            double simulate (const Model_public_state &, const Cell &);
            int update_particles(const Model_public_state &);
            std::vector<Model_state> particles;
        };
    }