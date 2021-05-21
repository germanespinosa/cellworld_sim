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

    bool Generative_model::evolve(Move move) {
        if (state.public_state.current_turn != observer_index) throw logic_error("bad particle");
        observer().set_move(std::move(move));
        return update();
    }

    bool Generative_model::evolve() {
        auto next_agent = (observer_index + 1) % _agents.size();
        if (state.public_state.current_turn != next_agent) throw logic_error("bad particle");
        while ( state.public_state.current_turn != observer_index && update() );
        return state.public_state.status == Running;
    }
}