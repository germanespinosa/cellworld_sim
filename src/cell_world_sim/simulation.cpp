#include <cell_world_sim/simulation.h>

cell_world::sim::Simulation::Simulation(const cell_world::sim::Static_data &data):
model(data.cells){
    model.add_agent(Prey::create(data));
    model.add_agent(Predator::create(data));
}

void cell_world::sim::Simulation::run() {
    model.run();
}
