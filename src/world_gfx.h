#ifndef __WORLD_GFX_H__
#define __WORLD_GFX_H__
#include <list>
#include "drawable.h"

class world_gfx : public drawable
{
    public:
        void draw(sys::gfx * gfx);
    private:
        std::list<drawable *> m_gobjects;
};

#endif /* __WORLD_GFX_H__ */
