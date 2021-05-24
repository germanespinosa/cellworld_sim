#include <cell_world_sim/forward_information_search.h>
#include <cmath>
using namespace std;

namespace cell_world::sim {

    Forward_information_search::Forward_information_search(Generative_model &generative_model, unsigned int simulation_count):
    generative_model(generative_model),
    lppo(generative_model.data.lppo),
    simulation_count(simulation_count){ }

    Move Forward_information_search::get_best(Belief_state &belief_state) {
        auto &lppo_graph = generative_model.data.lppo;
        auto cell = belief_state[0].public_state.agents_state[generative_model.observer_index].cell;
        auto &observer = generative_model.observer();
        Decision_tree tree(lppo_graph, cell);
        for (unsigned int simulation = 0 ; simulation < simulation_count ; simulation){
            auto &particle = belief_state.random_particle();
            generative_model.set_state(particle);
            auto &current_cell = generative_model.observer().public_state().cell;
            while (generative_model.state.public_state.status == Model_public_state::Running) {
                tree.expansion();
                tree.selection();
                auto &destination = tree.current->cell;
                while (current_cell != destination
                        && generative_model.evolve()){
                    auto move = generative_model.data.paths.get_move(current_cell,destination);
                    observer.set_move(move);
                }
            }
        }
        return  generative_model.data.paths.get_move(cell, tree.best().cell);
    }

    Decision_tree::Decision_tree(const Graph &lppo, const Cell &root):
        lppo(lppo),
        current(this),
        Decision_tree_node(nullptr, root) {}

    void Decision_tree::expansion() {
        auto &options = lppo[current->cell];
        for (auto &option:options){
            children.emplace_back(current,option);
        }
    }

    void Decision_tree::selection() {
        current = &select();
    }

    Decision_tree_node &Decision_tree::best() {
        unsigned int best_index = 0;
        for (unsigned int child_index=1;child_index<children.size();child_index++){
            if (children[best_index].reward<children[child_index].reward){
                best_index = child_index;
            }
        }
        return children[best_index];
    }

    Decision_tree_node &Decision_tree_node::select() {
        double Ni = 0;
        for (auto &child : children) Ni += child.count;
        double lnNi = log (Ni);
        double c = 1; // exploitation vs exploration (0 = no exploration)
        int selected_child;
        double max_ubc1;
        for (int child_index = 0; child_index < children.size(); child_index++) {
            double ni = children[child_index].count;
            double exploitation = children[child_index].reward; // wi/ni
            double exploration = sqrt(lnNi/ni);
            double tie_breaker = Chance::dice_double(.000001);
            double ucb1 = exploitation + c * exploration + tie_breaker;
            if (child_index == 0 || max_ubc1 < ucb1) {
                selected_child = child_index;
                max_ubc1 = ucb1;
            }
        }
        return children[selected_child];
    }

    Decision_tree_node::Decision_tree_node(Decision_tree_node *parent, const Cell &cell) :
    reward(0), count(0), parent(parent), cell(cell){}
}

