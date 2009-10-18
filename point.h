#ifndef __POINT_H__
#define __POINT_H__
#include "object.h"

namespace phys {

class point : public simobject<SIMOBJECT_POINT, 1>
{
	public:
		point(double mass, double x, double y, double z = 0);
		virtual ~point();
		vertex_t & get_pos()
		{
		    return m_vertices[0];
		}
		vector_t & get_velocity()
		{
		    return m_velocity;
		}
		double get_1_over_mass()
		{
		    return m_1_over_mass;
		}
		double get_mass()
		{
		    return m_mass;
		}
        double distance(const pos_t & p)
        {
            return 0.0;
        }
        bool is_collision(const pos_t & p)
        {
            return false;
        }
	private:
		double m_mass;
		double m_1_over_mass;
		vector_t m_velocity;
};

}
#endif /* __POINT_H__ */
