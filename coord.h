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
        bool visible(ublas::vector<double> & v);
	private:
        typedef enum {
            LINE_H = 0,
            LINE_V,
        } line_type_t;

        void hline(gfx * g);
        void vline(gfx * g);
        void line(gfx * g, ublas::vector<double> & start, ublas::vector<double> & end, line_type_t t);
        void ticks(gfx * g);
        double m_width;
        double m_height;
        double m_sc_width;
        double m_sc_height;
        ublas::vector<double> m_offs;

};

}
#endif /* __COORD_H__ */
