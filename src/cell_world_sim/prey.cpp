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
        auto destination = data.map[Coordinates{0,-7}];
        auto move = data.paths.get_move(public_state().cell, destination);
        cout << "Prey move: " << move << endl;
        return move;
    }

    const Cell &Prey::start_episode() {
        auto &cell = data.map[Coordinates{0,7}];
        cout << "Prey Starts: " << cell.coordinates << endl;
        return cell;
    }

    cell_world::Agent_status_code Prey::update_state(const Model_public_state &state) {
        cout << "Prey cell: " << public_state().cell.coordinates << " going to " << Coordinates{0,-7} <<endl;
        if (public_state().cell.coordinates == Coordinates{0,-7}) {
            return Finished;
        }
        return Running;
    }
}