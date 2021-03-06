#ifndef __COORD_H__
#define __COORD_H__
#include <boost/numeric/ublas/vector.hpp>
#include "gfx.h"
#include "object.h"
#include "object_types.h"
#include "drawable.h"

using namespace boost::numeric;

class coord : public drawable
{

	public:
        typedef enum {
            TO_SCREEN,
            FROM_SCREEN,
        } translation_type_t;

		coord();
        virtual ~coord();
        void init(double width, double height, double sc_width, double sc_height);
        pos_t translate(pos_t & p, translation_type_t type = TO_SCREEN);
        void translate_inside(pos_t & p, translation_type_t type = TO_SCREEN);
        void draw(sys::gfx * g, coord * c);
        bool visible(pos_t & p);
        void get_dimensions(dimensions_t & world_dim, dimensions_t & screen_dim);
	private:
        typedef enum {
            LINE_H = 0,
            LINE_V,
        } line_type_t;

        void hline(sys::gfx * g);
        void vline(sys::gfx * g);
        void line(sys::gfx * g, vertex_t & start, vertex_t & end, line_type_t t);
        void ticks(sys::gfx * g);

        double          m_width;
        double          m_height;
        double          m_sc_width;
        double          m_sc_height;
        vector_t        m_offs;

};
#endif /* __COORD_H__ */
