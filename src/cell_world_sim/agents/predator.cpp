#include <cell_world_sim/agents/predator.h>
using namespace cell_world;
using namespace std;

namespace  cell_world::sim {
    std::vector<Predator> Predator::predators;
    Agent_base &Predator::create(const Static_data &data) {
        Predator::predators.emplace_back(data);
        return *(--Predator::predators.end());
    }

    Predator::Predator(const Static_data &data) :
    data(data),
    start(data.map[Coordinates{0,-7}])
    {
        prey_index = Not_found;
        for (int i = 0;i<data.agents.size();i++ ){
            auto agent_type = data.agents[i];
            if (agent_type == Static_data::Agent_type::prey){
                prey_index = i;
            }
        }
        if (prey_index == Not_found) throw logic_error("predator agent needs at least one prey");
    }

    cell_world::Move Predator::get_move(const Model_public_state &state) {
        auto &prey_location = state.agents_state[prey_index].cell;
        auto move = data.paths.get_move(public_state().cell, prey_location);
        cout << "Predator move: " << move <<  endl;
        return move;
    }

    const Cell &Predator::start_episode() {
        return start;
    }

    cell_world::Agent_status_code Predator::update_state(const Model_public_state &state) {
        auto &prey_location = state.agents_state[prey_index].cell;
        if (prey_location == public_state().cell) return Finished;
        return Running;
    }
}