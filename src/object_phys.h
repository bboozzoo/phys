#ifndef __OBJECT_PHYS_H__
#define __OBJECT_PHYS_H__
#include <ode/ode.h>
#include "object_types.h"

class world_phys;

class object_phys
{
    public:
        object_phys(world_phys * world, object::type_t type);
        set_mass(double mass, double density);
        set_geometry(dimensions_t dim);
        set_position(pos_t pos);
        get_position(pos_t & pos);
    private:

        dBodyID         m_body; /* body descriptor */
        dGeomID         m_geom; /* body geometry descriptor */
        object::type    m_type; /* type: box, sphere.. */
        dimensions_t    m_dim;
        pos_t           m_pos;
};

#endif /* __OBJECT_PHYS_H__ */
