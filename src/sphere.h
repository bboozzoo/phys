#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "object_phys.h"
#include "drawable.h"

class world;

class sphere : public object_phys, public drawable
{
	public:
		sphere(world * w, double mass, double radius, double x, double y, double z = 0);
		virtual ~sphere();
        virtual void draw(sys::gfx * gfx, coord * c);
	private:
        double m_radius;
};

#endif /* __SPHERE_H__ */

