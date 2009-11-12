#include "object_phys.h"

object_phys::object_phys(world_phys * world, object::type_t type) 
    : m_body(NULL), m_geom(NULL), m_type(type)
{
    m_body = dBodyCreate(world->get_phys_world());
    if (m_body != NULL) {
        dBodySetData(m_body, (void *) this);
    }
}

void
object_phys::set_geometry(dimensions_t dim)
{
    m_dim = dim;
    switch (m_type) 
    {
        case object::SPHERE:
            m_geom = dCreateSphere(world->get_phys_space(), dim[0]);
            break;
        case object::BOX:
            m_geom = dCreateBox(worl->get_phys_space(), dim[0], dim[1], dim[2]);
            break;
        default:
            break;
    };
}

void
object_phys::set_mass(double mass, double density)
{
    dMass m;
    switch (m_type)
    {
        case object::SPHERE:
            dMassSetSphere(&m, density, m_dim[0]);
            break;
        case object::BOX:
            dMassSetBox(&m, density, m_dim[0], m_dim[1], m_dim[2]);
            break;
        default:
            abort();
    }
    dBodySetMass(m_body, &m);
}

void
object_phys::set_position(pos_t pos) 
{
    if (m_body != NULL)
    {
        if (pos.size() == 2)
        {
            pos.resize(3);
            pos[2] = 0;
        }
        m_pos = pos;
        dBodySetPosition(m_body, pos[0], pos[1], pos[2]);
    }
}

