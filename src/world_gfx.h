#ifndef __WORLD_GFX_H__
#define __WORLD_GFX_H__
#include <list>
#include "drawable.h"

class world_gfx : public drawable
{
    public:
        world_gfx();
        virtual ~world_gfx();
        void draw(sys::gfx * gfx, coord * c);
        void add(drawable * og); 
    protected:
        std::list<drawable *> m_gobjects;
};

#endif /* __WORLD_GFX_H__ */
