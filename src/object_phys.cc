#include "world_phys.h"
#include "object_phys.h"
#include "log.h"

object_phys::object_phys(world_phys * world, object::type_t type) 
    : object_base(type), m_world(world), m_body(NULL), m_geom(NULL)
{
    LOG(1, "creating object at: "  << (void *) this << " phys, world: " << (void *) world << " type: " << type);
    m_body = dBodyCreate(world->get_phys_world());
    if (m_body != NULL) {
        dBodySetData(m_body, (void *) this);
    }
}

object_phys::~object_phys()
{
    LOG(1, "destroying object at " << (void *) this);
    dBodyDestroy(m_body);
    /* body destroy ??? */
}

void
object_phys::set_geometry(dimensions_t & dim)
{
    LOG(1, "object at: " << (void *) this << " setting geometry: " << dim);
    m_dim = dim;
    switch (m_type) 
    {
        case object::SPHERE:
            m_geom = dCreateSphere(m_world->get_phys_space(), dim[0]);
            break;
        case object::BOX:
            m_geom = dCreateBox(m_world->get_phys_space(), dim[0], dim[1], dim[2]);
            break;
        default:
            break;
    };
}

void
object_phys::set_density(double density)
{
    LOG(1, "object at: " << (void *) this << " setting density: " << density);
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
object_phys::set_position(pos_t & pos) 
{
    LOG(1, "object at: " << (void *) this << " setting position: " << pos);
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

void 
object_phys::get_position(pos_t & pos) 
{ 
    const dReal * p = dBodyGetPosition(m_body);
    m_pos[0] = p[0];
    m_pos[1] = p[1];
    m_pos[2] = p[2];
    LOG(2, "object at: " << (void *) this << " position: " << m_pos);
    pos = m_pos; 
}

