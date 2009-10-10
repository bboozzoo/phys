#ifndef __POINT_H__
#define __POINT_H__
#include <boost/numeric/ublas/vector.hpp>
using namespace boost::numeric;
namespace phys {

class point 
{
	public:
		point(double mass, double x, double y, double z = 0);
		virtual ~point();
        ublas::vector<double> & get_pos()
        {
            return m_pos;
        }
        ublas::vector<double> & get_velocity()
        {
            return m_velocity;
        }
        ublas::vector<double> & get_force()
        {
            return m_force;
        }
	private:
		double m_mass;
        double m_1_over_mass;
        ublas::vector<double> m_pos;
        ublas::vector<double> m_velocity;
        ublas::vector<double> m_force;
};

}
#endif /* __POINT_H__ */
