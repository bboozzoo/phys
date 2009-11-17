#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__
#include "gfx.h"

class coord;
class drawable 
{
    public:
        drawable(sys::color c);
        drawable();
        ~drawable();
        virtual void draw(sys::gfx * gfx, coord * c) = 0;
        void set_color(sys::color & c);
    protected:
        sys::color   m_color;
};


#endif /* __DRAWABLE_H__ */
