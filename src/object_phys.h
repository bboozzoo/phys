#ifndef __OBJECT_PHYS_H__
#define __OBJECT_PHYS_H__
#include <ode/ode.h>
#include "object_types.h"
#include "object_base.h"

class world_phys;

class object_phys : public object_base
{
    public:
        object_phys(world_phys * world, object::type_t type);
        virtual ~object_phys();
        void set_density(double density);
        void set_geometry(dimensions_t & dim);
        void set_position(pos_t & pos);
        void get_position(pos_t & pos);
        dBodyID get_body() { return m_body; }
        dGeomID get_geom() { return m_geom; }
    private:

        dBodyID         m_body; /* body descriptor */
        dGeomID         m_geom; /* body geometry descriptor */
        dimensions_t    m_dim;
        pos_t           m_pos;
        world_phys *    m_world;
};

#endif /* __OBJECT_PHYS_H__ */
