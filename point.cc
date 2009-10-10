#include "point.h"

namespace phys 
{

point::point(double mass, double x, double y, double z)
    : m_mass(mass), m_pos(3), m_velocity(3), m_force(3)
{
    if (mass == 0)
        m_mass = 1;
    m_1_over_mass = 1/m_mass;
     
    m_pos(0) = x;
    m_pos(1) = y;
    m_pos(2) = z;
}

point::~point()
{
}

}
