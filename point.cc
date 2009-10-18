#include "point.h"
#include "log.h"

namespace phys 
{

point::point(double mass, double x, double y, double z)
    : m_mass(mass), m_velocity(2)
{
    validate_mass(); 
    pos_t & p = m_vertices[0];
    p.resize(2);
    p(0) = x;
    p(1) = y;

    m_velocity(0) = 0;
    m_velocity(1) = 0;

    LOG(1, "m: " << m_mass << " p: " << m_vertices[0] << " v: " << m_velocity);
}

point::point(double mass, pos_t pos, vector_t vel)
    : m_mass(mass), m_velocity(vel)
{
    validate_mass();
    m_vertices[0] = pos;
    LOG(1, "m: " << m_mass << " p: " << m_vertices[0] << " v: " << m_velocity);
}

point::~point()
{
}

void
point::validate_mass()
{
    if (m_mass == 0)
        m_mass = 1.0;
    m_1_over_mass = 1.0/m_mass;
}

}
