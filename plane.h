#ifndef __PLANE_H__
#define __PLANE_H__
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace boost::numeric;

namespace phys
{

class plane
{
	public:
		plane();
		~plane();
		void init(ublas::vector<double> p1, ublas::vector<double> p2);
		ublas::vector<double> & get_normal();
		ublas::vector<double> & get_p();
		
	private:
		ublas::vector<double> m_p1;
		ublas::vector<double> m_p2;
		ublas::vector<double> m_normal;
};

}
#endif /* __PLANE_H__ */
