#ifndef __PLANE_H__
#define __PLANE_H__
#include "object_phys.h"
#include "drawable.h"
#include "coord.h"

class world;

class plane : public object_phys, public drawable
{
	public:
		plane(world * w, vector_t normal, double d);
		~plane();
        void draw(sys::gfx * gfx, coord * c);
        vector_t & get_normal();

	private:
        vertex_t        m_p[2];
        /* 
         * line eq in 3D: Ax + By + Cz + D = 0
         * normal N is [A, B, C] 
         */
		vector_t        m_normal;
        double          m_d;
};

#endif /* __PLANE_H__ */

