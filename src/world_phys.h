#ifndef __WORLD_PHYS_H__
#define __WORLD_PHYS_H__
#include <list>
#include <ode/ode.h>
#include "object_phys.h"

class world_phys
{
    public:
        world_phys();
        virtual ~world_phys();
        void advance(double delta_t);
        dWorldID get_phys_world() { return m_world; }
        dSpaceID get_phys_space() { return m_space; }
        void add(object_phys * op);
    protected:
        std::list<object_phys *> m_pobjects;
        dWorldID    m_world;
        dSpaceID    m_space;
        dJointID    m_2d_plane;
};


#endif /* __WORLD_PHYS_H__ */
