#ifndef __PLANE_H__
#define __PLANE_H__
#include "object.h"

namespace phys
{

class plane : public simobject<SIMOBJECT_PLANE, 2>
{
	public:
		plane();
		~plane();
		void init(vertex_t p1, vertex_t p2);
        vector_t & get_normal();
		vector_t & get_nn();
		double get_p();
        vertex_t & get_p1();
        vertex_t & get_p2();
        bool is_inside(const pos_t & p);
        double distance(const pos_t & p)
        {
            return 0.0;
        }
        bool is_collision(const pos_t & p)
        {
            return false;
        }

		
	private:
		vertex_t * m_start_x;
		vertex_t * m_end_x;
		vertex_t * m_start_y;
		vertex_t * m_end_y;
        /* 
         * line eq in 2D: Ax + By + C = 0
         * normal N is [A, B] 
         * vector in line is [-B, A] 
         */
		vector_t m_normal;
        double m_c;
        /* 
         * represent plane/line in hessian normal form
         * n * x = -p
         * n - normalized normal
         * p = C / |N|
         */
        vector_t m_n;
        double m_p;
};

}
#endif /* __PLANE_H__ */
