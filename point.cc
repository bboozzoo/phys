#include "point.h"
#include "log.h"

namespace phys 
{

point::point(double mass, double x, double y, double z)
    : m_mass(mass), m_pos(3), m_velocity(3)
{
    if (mass == 0)
        m_mass = 1;
    m_1_over_mass = 1/m_mass;
    
    m_pos(0) = x;
    m_pos(1) = y;
    m_pos(2) = z;

    for (int i = 0; i < 3; i++)
    {
        m_velocity(i) = 0;
    }

    LOG(2, "m: " << m_mass << " p: " << m_pos << " v: " << m_velocity);
}

point::~point()
{
}

}
