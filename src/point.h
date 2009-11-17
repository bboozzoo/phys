#ifndef __POINT_H__
#define __POINT_H__
#include "object_phys.h"
#include "drawable.h"
#include "sphere.h"

class world;

class point : public sphere
{
	public:
		point(world * w, double mass, double x, double y, double z = 0);
		virtual ~point();
	private:
};

#endif /* __POINT_H__ */
