#pragma once
#include <cell_world.h>
#include <cell_world_sim/static_data.h>
#include <cell_world_sim/agents/predator_predictor.h>

namespace cell_world::sim {
    struct Belief_state : std::vector<Model_state> {
        Belief_state(Generative_model &, int, int);
        Model_state &random_particle();
        void filter();
        Generative_model &generative_model;
        unsigned int particle_count;
        void record_observation(Model_public_state &observation);
        std::vector<Model_public_state> observations;
        Move_list observer_moves;
    private:
        void replace_particle(Model_state &);
        bool is_valid(Model_state &, Model_public_state &);
    };
}