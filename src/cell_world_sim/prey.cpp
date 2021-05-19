#include <cell_world_sim/prey.h>

using namespace cell_world;
using namespace std;

namespace  cell_world::sim {
    std::vector<Prey> Prey::preys;
    Agent_base &Prey::create(const Static_data &data) {
        Prey::preys.emplace_back(data);
        return *(--Prey::preys.end());
    }

    Prey::Prey(const Static_data &data) : data(data) {

    }

    Move Prey::get_move(const Model_public_state &state) {
        cout << "Prey Turn:" << state.agents_state[state.current_turn].iteration << endl;
        return Move{0,0};
    }

    const Cell &Prey::start_episode() {
        cout << "Prey Starts" << endl;
        return data.map[Coordinates{0,7}];
    }
}