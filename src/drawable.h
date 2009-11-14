#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__
#include "gfx.h"

class coord;
class drawable 
{
    public:
        virtual void draw(sys::gfx * gfx, coord * c) = 0;

};
#endif /* __DRAWABLE_H__ */
