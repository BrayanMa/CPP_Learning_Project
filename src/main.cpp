#include "tower_sim.hpp"

int main(int argc, char** argv)
{
    /*Point<float, 3> p1;
    Point<float, 3> p2;
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3;*/
    ContextInitializer context_initializer = ContextInitializer {argc , argv};
    TowerSimulation simulation { context_initializer };
    simulation.launch();

    return 0;
}