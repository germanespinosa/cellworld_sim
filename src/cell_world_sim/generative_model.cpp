#include <cell_world_sim/generative_model.h>

#include <utility>

using namespace std;

namespace cell_world::sim {

    Move Observer::get_move(const Model_public_state &) {
        return next_move;
    }

    void Observer::set_move(Move move) {
        next_move = std::move(move);
    }

    Generative_model::Generative_model(const Static_data &data): data(data), Model(data.cells) {

    }

    void Generative_model::add_observer(Observer &observer) {
        observer_index = _agents.size();
        add_agent(observer);
    }

    Model_state Generative_model::create_particle() {
        start_episode();
        return state;
    }


    bool Generative_model::evolve() {
        if (state.public_state.current_turn == observer_index)
            return update();
        while ( state.public_state.current_turn != observer_index && update() );
        return state.public_state.status == Model_public_state::Status::Running;
    }

    Observer &Generative_model::observer() {
        return (Observer &) (Agent_base &) _agents[observer_index];
    }
}