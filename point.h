#ifndef __POINT_H__
#define __POINT_H__
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

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
		double get_1_over_mass()
		{
		    return m_1_over_mass;
		}
		double get_mass()
		{
		    return m_mass;
		}
	private:
		double m_mass;
		double m_1_over_mass;
		ublas::vector<double> m_pos;
		ublas::vector<double> m_velocity;
};

}
#endif /* __POINT_H__ */
