#ifndef __WORLD_PHYS_H__
#define __WORLD_PHYS_H__
#include <list>
#include "physical.h"

class world_phys
{
    public:
        void advance(double delta_t);
        dWorldID get_phys_world() { return m_world; }
        dSpaceID get_phys_space() { return m_space; }
    private:
        std::list<object_phys *> m_pobjects;
};


#endif /* __WORLD_PHYS_H__ */
