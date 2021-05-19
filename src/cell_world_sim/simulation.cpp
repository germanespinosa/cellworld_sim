#include <cell_world_sim/simulation.h>

cell_world::sim::Simulation::Simulation(const cell_world::sim::Static_data &data):
model(data.cells){
    for (auto agent_type : data.agents){
        switch (agent_type) {
            case Static_data::predator:
                model.add_agent(Predator::create(data));
                break;
            case Static_data::prey:
                model.add_agent(Prey::create(data));
                break;
        }
    }
}

void cell_world::sim::Simulation::run() {
    model.run();
}
