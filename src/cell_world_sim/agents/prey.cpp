#include <cell_world_sim/agents/prey.h>
#include <cell_world_sim/agents/predator_predictor.h>

using namespace cell_world;
using namespace std;

namespace  cell_world::sim {

    struct Mini_prey : Stateful_agent<Predictor_state>{
        static Agent_base &create() {
            Mini_prey::preys.emplace_back();
            return *(--Prey::preys.end());
        }
        static vector<Mini_prey> preys;
    };

    vector<Mini_prey> Mini_prey::preys;
    std::vector<Prey> Prey::preys;

    Agent_base &Prey::create(const Static_data &data, const Cell &start) {
        Prey::preys.emplace_back(data, start);
        return *(--Prey::preys.end());
    }

    Prey::Prey(const Static_data &data, const Cell &start) :
    data(data),
    start(start),
    goal(data.burrow),
    generative_model(data),
    belief_state(generative_model, 100,1000){
        predator_index = Not_found;
        for (int i = 0; data.agents.size(); i++){
            auto agent = data.agents[i];
            switch (agent.type) {
                case Static_data::predator:
                    predator_index = 0;
                    generative_model.add_agent(Predator_predictor::create(data));
                    break;
                case Static_data::prey:
                    generative_model.add_agent(Mini_prey::create());
                    break;
            }
        }
    }

    Move Prey::get_move(const Model_public_state &state) {
        auto &prey_location = public_state().cell;
        auto &predator_location = state.agents_state[predator_index].cell;

        auto options = data.graph[prey_location];
        vector<double> rewards(options.size(), 0);
        vector<int> counters(options.size(),0);
        for (int s=0; s<data.simulations;s++ ){
            auto option_index = Chance::dice(options.size());
            auto &option = options[option_index];
            double result = simulate (state, option);
            rewards[option_index] = (rewards[option_index] * (float)counters[option_index] + result) / ( (float)counters[option_index] + 1);
            counters[option_index]++;
        }
        auto best_option_index = Chance::pick_best(1.0,rewards);
        auto &best_option = options[best_option_index];
        auto move = data.paths.get_move(public_state().cell, best_option);
        return move;
    }

    const Cell &Prey::start_episode() {
        return start;
    }

    cell_world::Agent_status_code Prey::update_state(const Model_public_state &state) {
        if (public_state().cell == goal) return Finished;
        return Running;
    }

    double Prey::simulate(const Model_public_state &state, const Cell &option) {
        return 0;
    }
}