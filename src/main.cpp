#include <cell_world_sim.h>
#include <cell_world.h>
#include <cell_world_tools.h>

using namespace cell_world;
using namespace cell_world::sim;
using namespace json_cpp;
using namespace std;

int main(){
    World w = Json_create<World>(Web_resource::from("world").key("world_0_0").get());
    auto cells = w.create_cell_group();
    Static_data data(cells);
    Simulation s(data);
    s.run();

    cout << "MAP :" << data.map.coordinates << endl;
    cout << "CELLS :" << data.cells << endl;
}