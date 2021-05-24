#pragma once
#include <cell_world.h>
#include <cell_world_sim/generative_model.h>
#include <cell_world_sim/belief_state.h>

namespace cell_world::sim {

    struct Decision_tree_node{
        explicit Decision_tree_node(Decision_tree_node *, const Cell &);
        double reward;
        unsigned int count;
        Decision_tree_node *parent;
        const Cell &cell;
        std::vector<Decision_tree_node> children;
        Decision_tree_node &select();
    };

    struct Decision_tree : Decision_tree_node {
        explicit Decision_tree(const Graph &, const Cell &);
        void expansion();
        void selection();
        Decision_tree_node &best();
        const Graph &lppo;
        Decision_tree_node *current;
    };

    struct Forward_information_search{
        explicit Forward_information_search(Generative_model &, unsigned int);
        Generative_model &generative_model;
        const Graph &lppo;
        Move get_best(Belief_state &);
        unsigned int simulation_count;
    };
}