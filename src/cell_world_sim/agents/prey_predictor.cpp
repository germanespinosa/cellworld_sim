#include <cell_world_sim/agents/prey_predictor.h>

using namespace std;
using namespace cell_world;

namespace cell_world::sim{

    Move Prey_predictor::get_move(const Model_public_state &) {
        auto move = data.paths.get_move(public_state().cell, goal);
        return move;
    }

    Agent_status_code Prey_predictor::update_state(const Model_public_state &) {
        cout << "Prey cell: " << public_state().cell.coordinates << " going to " << Coordinates{0,-7} <<endl;
        if (public_state().cell == goal) {
            return Finished;
        }
        return Running;
    }

    const Cell &Prey_predictor::start_episode() {
        return start;
    }

    Prey_predictor::Prey_predictor(const Static_data &data):
    data(data){
        start = data.map[Coordinates{0,7}];
        goal = data.map[Coordinates{0,-7}];
    }
}