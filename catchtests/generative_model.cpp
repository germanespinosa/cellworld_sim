#include <catch.h>
#include <cell_world_tools.h>
#include <cell_world_sim/generative_model.h>
#include <cell_world_sim/static_data.h>

using namespace cell_world;
using namespace cell_world::sim;
using namespace std;

struct Test_agent : Observer {
    explicit Test_agent( const Cell &start):
    start(start){};
    const Cell &start_episode() override{
        return start;
    };
    const Cell &start;
};


TEST_CASE("generative_model") {
    Static_data data ("world_0_0");
    Test_agent a1 (data.map[{0,7}]);
    a1.set_move({0,-1});
    Test_agent a2 (data.map[{0,-7}]);
    a2.set_move({0,1});
    Generative_model gm(data);
    gm.add_agent(a1);
    gm.add_observer(a2);
    gm.start_episode();
    CHECK(gm.state.public_state.agents_state[0].cell == data.map[{0,7}]);
    CHECK(gm.state.public_state.agents_state[1].cell == data.map[{0,-7}]);
    CHECK(gm.observer().public_state().cell == data.map[{0,-7}]);
    a1.set_move({0,-1});
    gm.update();
    CHECK(a1.public_state().cell == data.map[{0,6}]);
    gm.observer().set_move({0,1});
    gm.update();
    CHECK(gm.observer().public_state().cell == data.map[{0,-6}]);
    gm.update();
    CHECK(a1.public_state().cell == data.map[{0,5}]);
    gm.update();
    CHECK(gm.observer().public_state().cell == data.map[{0,-5}]);
}