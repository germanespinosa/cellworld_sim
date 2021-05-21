#pragma once
#include <cell_world.h>
#include <cell_world_sim/static_data.h>

namespace cell_world::sim {
    struct Observer : Stateless_agent {
        Move get_move(const Model_public_state &) override;
        void set_move(Move);
        Move next_move;
    };

    struct Generative_model : Model {
        explicit Generative_model(const Static_data &);
        void add_observer(Observer &);
        Model_state create_particle();
        bool evolve();
        Observer &observer();
        Static_data data;
        unsigned int observer_index;
    };
}