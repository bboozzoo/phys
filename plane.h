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
		ublas::vector<double> & get_nn();
		double get_p();
        ublas::vector<double> & get_p1();
        ublas::vector<double> & get_p2();
        bool is_inside(ublas::vector<double> & p);

		
	private:
		ublas::vector<double> m_p1;
		ublas::vector<double> m_p2;
		ublas::vector<double> * m_start_x;
		ublas::vector<double> * m_end_x;
		ublas::vector<double> * m_start_y;
		ublas::vector<double> * m_end_y;
        /* 
         * line eq in 2D: Ax + By + C = 0
         * normal N is [A, B] 
         * vector in line is [-B, A] 
         */
		ublas::vector<double> m_normal;
        double m_c;
        /* 
         * represent plane/line in hessian normal form
         * n * x = -p
         * n - normalized normal
         * p = C / |N|
         */
        ublas::vector<double> m_n;
        double m_p;
};

}
#endif /* __PLANE_H__ */
