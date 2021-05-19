#include <cell_world_sim/agents/predator_predictor.h>

using namespace std;
namespace cell_world::sim{
    vector<Predator_predictor> Predator_predictor::predators;

    Agent_base &Predator_predictor::create(const Static_data &data) {
        Predator_predictor::predators.emplace_back(data);
        return *(--Prey::preys.end());
    }

    cell_world::Move Predator_predictor::get_move(const Model_public_state &state) {
        auto &prey_location = state.agents_state[prey_index].cell;
        auto &predator_location = public_state().cell;
        if (data.visibility[predator_location].contains(prey_location)){
            return data.paths.get_move(predator_location,prey_location);
        }
        auto move = data.paths.get_move(predator_location,data.inverted_visibility[predator_location].random_cell());
        return move;
    }

    cell_world::Agent_status_code Predator_predictor::update_state(const Model_public_state &) {
        return Running;
    }

    const Cell &Predator_predictor::start_episode() {
        return start;
    }

    Predator_predictor::Predator_predictor(const Static_data &data):
            data(data){
        prey_index = Not_found;
        for (int i = 0;i<data.agents.size();i++ ){
            auto agent = data.agents[i];
            if (agent.type == Static_data::Agent_type::prey){
                prey_index = i;
            }
        }
        if (prey_index == Not_found) throw logic_error("predator agent needs at least one prey");
    }
}