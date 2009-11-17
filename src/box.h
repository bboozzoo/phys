#ifndef __BOX_H__
#define __BOX_H__
#include "object_phys.h"
#include "drawable.h"

class world;

class box : public object_phys, public drawable
{
	public:
		box(world * w, double mass, double x, double y, double z = 0);
		virtual ~box();
        virtual void draw(sys::gfx * gfx, coord * c);
};

#endif /* __BOX_H__ */
