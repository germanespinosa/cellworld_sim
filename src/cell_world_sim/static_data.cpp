#include <cell_world_sim/static_data.h>
#include <cell_world_tools.h>

using namespace cell_world;
using namespace cell_world::sim;
using namespace json_cpp;

cell_world::sim::Static_data::Static_data(const std::string &world_name) :
    world (Json_create<World>(Web_resource::from("world").key(world_name).get())),
    cells(world.create_cell_group()),
    map(cells),
    paths(world.create_paths(
            Json_create<Path_builder>(
                    Web_resource::from("paths").key(world.name).key("astar").get()
            )
          )
    )
{

}
