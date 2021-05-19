#include <cell_world_sim/predator.h>
using namespace cell_world;
using namespace std;

namespace  cell_world::sim {
    std::vector<Predator> Predator::predators;
    Agent_base &Predator::create(const Static_data &data) {
        Predator::predators.emplace_back(data);
        return *(--Predator::predators.end());
    }

    Predator::Predator(const Static_data &data) : data(data){

    }

    cell_world::Move Predator::get_move(const Model_public_state &state) {
        cout << "Predator Turn:" << state.agents_state[state.current_turn].iteration << endl;
        return Move{0,0};
    }

    const Cell &Predator::start_episode() {
        cout << "Predator Starts" << endl;
        return data.map[Coordinates{0,-7}];
    }
}