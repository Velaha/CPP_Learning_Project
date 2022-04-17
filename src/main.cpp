#include "Point.hpp"
#include "tower_sim.hpp"

void test_generic_points()
{

    Point<1, int> p1;
    Point<1, int> p2;
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3; // ou 3.f, ou 3.0 en fonction du type de Pointv2}

    // Point2D p4 = Point2D { 1, 2, 3 };
    // Point3D p5 { 1, 2 };
    // std::cout << p5.z() << std::endl;
}

int main(int argc, char** argv)
{
    test_generic_points();
    TowerSimulation simulation { argc, argv };
    simulation.launch();

    return 0;
}