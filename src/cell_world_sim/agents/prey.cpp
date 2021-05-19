#include <cell_world_sim/agents/prey.h>

using namespace cell_world;
using namespace std;

namespace  cell_world::sim {
    std::vector<Prey> Prey::preys;
    Agent_base &Prey::create(const Static_data &data) {
        Prey::preys.emplace_back(data);
        return *(--Prey::preys.end());
    }

    Prey::Prey(const Static_data &data) :
    data(data),
    start(data.map[Coordinates{0,7}]),
    goal(data.map[Coordinates{0,-7}]){
    }

    Move Prey::get_move(const Model_public_state &state) {
        auto move = data.paths.get_move(public_state().cell, goal);
        cout << "Prey move: " << move << endl;
        return move;
    }

    const Cell &Prey::start_episode() {
        return start;
    }

    cell_world::Agent_status_code Prey::update_state(const Model_public_state &state) {
        if (public_state().cell == goal) {
            return Finished;
        }
        return Running;
    }
}