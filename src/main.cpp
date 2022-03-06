#include "tower_sim.hpp"

int main(int argc, char** argv)
{
    ContextInitializer context_initializer = ContextInitializer {argc , argv};
    TowerSimulation simulation { context_initializer };
    simulation.launch();

    return 0;
}