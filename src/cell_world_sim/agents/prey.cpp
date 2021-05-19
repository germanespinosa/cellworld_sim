#include <cell_world_sim/agents/prey.h>
#include <cell_world_sim/agents/predator_predictor.h>

using namespace cell_world;
using namespace std;

namespace  cell_world::sim {
    struct Mini_prey : Stateless_agent{
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
    generative_model(data.cells){
        for (auto agent : data.agents){
            switch (agent.type) {
                case Static_data::predator:
                    generative_model.add_agent(Predator_predictor::create(data));
                    break;
                case Static_data::prey:
                    generative_model.add_agent(Mini_prey::create());
                    break;
            }
        }
    }

    Move Prey::get_move(const Model_public_state &state) {
        auto move = data.paths.get_move(public_state().cell, goal);
        return move;
    }

    const Cell &Prey::start_episode() {
        return start;
    }

    cell_world::Agent_status_code Prey::update_state(const Model_public_state &state) {
        if (public_state().cell == goal) return Finished;
        return Running;
    }
}