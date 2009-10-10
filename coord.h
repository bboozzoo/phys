#ifndef __COORD_H__
#define __COORD_H__
#include <boost/numeric/ublas/vector.hpp>
#include "bin.h"
#include "gfx.h"

using namespace boost::numeric;
namespace phys {

class coord 
{
	public:
		coord();
        virtual ~coord();
        ublas::vector<double> translate(ublas::vector<double> & v);
        void init(double width, double height, double sc_width, double sc_height);
        void translate_inside(ublas::vector<double> & v);
        void draw(gfx * g);
	private:
        double m_width;
        double m_height;
        double m_sc_width;
        double m_sc_height;
        ublas::vector<double> m_offs;

};

}
#endif /* __COORD_H__ */
