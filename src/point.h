#ifndef __POINT_H__
#define __POINT_H__
#include "object_phys.h"
#include "drawable.h"

class world;

class point : public object_phys, public drawable
{
	public:
		point(world * w, double mass, double x, double y, double z = 0);
		virtual ~point();
        void draw(sys::gfx * gfx, coord * c);
	private:
};

#endif /* __POINT_H__ */
