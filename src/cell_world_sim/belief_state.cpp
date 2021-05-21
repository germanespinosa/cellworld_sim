#include <cell_world_sim/belief_state.h>

namespace cell_world::sim {

    Belief_state::Belief_state(Generative_model &generative_model, int particle_count, int max_tries):
    generative_model(generative_model){
        for (int i=0;i<max_tries;i++){
            push_back(generative_model.create_particle());
            if (size() == particle_count) break;
        }
        this->particle_count=size();
    }

    Model_state &Belief_state::random_particle() {
        return (*this)[Chance::dice(particle_count)];
    }

    void Belief_state::replace_particle(Model_state &particle) {
        bool valid_particle = false;
        while (!valid_particle) {
            particle = generative_model.create_particle();
            valid_particle = true;
            generative_model.set_state(particle);
            for (int o=0;o < observations.size() && is_valid(particle, observations[o]);o++){
                generative_model.observer().set_move(observer_moves[o]);
                generative_model.evolve();
            }
        }
    }

    bool Belief_state::is_valid(Model_state &particle, Model_public_state &observation) {
        auto &particle_observer_state = particle.public_state.agents_state[generative_model.observer_index];
        auto &particle_observer_cell = particle_observer_state.cell;
        auto &observation_observer_state = observation.agents_state[generative_model.observer_index];
        auto &observation_observer_cell = observation_observer_state.cell;
        if (observation_observer_cell != particle_observer_cell ) return false;
        auto &observer_cell = observation_observer_cell;
        auto &visibility = generative_model.data.visibility[observer_cell];
        for (int a=0;a<observation.agents_state.size();a++){
            if (a!=generative_model.observer_index) {
                auto particle_agent_cell = particle.public_state.agents_state[a].cell;
                auto observation_agent_cell = observation.agents_state[a].cell;
                if (observation_agent_cell != particle_agent_cell &&
                    (visibility.contains(observation_agent_cell) || visibility.contains(particle_agent_cell)) )
                    return false;
            }
        }
        return true;
    }

    void Belief_state::record_observation(Model_public_state &observation) {
        observations.push_back(observation);
        if (observations.size()>1){
            auto move = observation.agents_state[generative_model.observer_index].cell.coordinates - observations[observations.size()-2].agents_state[generative_model.observer_index].cell.coordinates;
            observer_moves.push_back(move);
        }else{
            observer_moves.emplace_back(0,0);
        }
        for (auto &particle:*this)
            if (!is_valid(particle,observation))
                replace_particle(particle);
    }
}