#ifndef __WORLD_H__
#define __WORLD_H__
#include "coord.h"
#include "world_gfx.h"
#include "world_phys.h"

class world : public world_phys, public world_gfx
{
    public:
        world(coord & coordinate_sys);
        ~world();
        void advance(double delta_t);
        void draw(sys::gfx * gfx);
        void setup();
    private:
        coord *     m_coord;

};
#endif /* __WORLD_H__ */
