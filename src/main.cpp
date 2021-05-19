#include <cell_world_sim.h>
#include <cell_world.h>

using namespace cell_world;
using namespace cell_world::sim;
using namespace json_cpp;
using namespace std;

int main(){
    Static_data data("world_0_0");
    data.agents.emplace_back(Static_data::prey,data.map[{0,-7}]);
    data.agents.emplace_back(Static_data::predator,data.map[{0,7}]);
    data.burrow = data.map[{0,7}];
    data.simulations = 5000;
    Simulation s(data);
    s.run();
    cout << "MAP :" << data.map.coordinates << endl;
    cout << "CELLS :" << data.cells << endl;
}