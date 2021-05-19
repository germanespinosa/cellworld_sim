#include <cell_world_sim.h>
#include <cell_world.h>

using namespace cell_world;
using namespace cell_world::sim;
using namespace json_cpp;
using namespace std;

int main(){
    Static_data data("world_0_0");
    data.agents.push_back(Static_data::prey);
    data.agents.push_back(Static_data::predator);
    Simulation s(data);
    s.run();
    cout << "MAP :" << data.map.coordinates << endl;
    cout << "CELLS :" << data.cells << endl;
}