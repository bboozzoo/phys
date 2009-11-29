#include <SDL/SDL_gfxPrimitives.h>
#include "world.h"
#include "plane.h"
#include "log.h"
#include "gfx_sdl.h"

using namespace boost::numeric;

plane::plane(world * w, vector_t normal, double d)
	: object_phys(w, object::PLANE), m_normal(3), m_d(0.0) 
{
    m_normal = normal;
    m_d = d;
    dimensions_t dim(4);
    dim[0] = m_normal[0];
    dim[1] = m_normal[1];
    dim[2] = m_normal[2];
    /* ODE's plane equation is a*x + b*y + c*z = d */
    dim[3] = -m_d;
    set_geometry(dim);

    /* calculate the points through which plane shall pass when drawing */
    for (int i = 0; i < 2; i++)
        m_p[i].resize(2);

    coord * c = w->get_coord();
    dimensions_t world_dim(2);
    dimensions_t screen_dim(2);
    c->get_dimensions(world_dim, screen_dim);

    double world_w_2 = world_dim[0] / 2.0;
    double world_h_2 = world_dim[1] / 2.0;

    if (m_normal[0] == 0.0) {
        m_p[0][0] = -world_w_2;
        m_p[1][0] = world_w_2;
        m_p[0][1] = m_p[1][1] = -d/m_normal[1];
    } else if (m_normal[1] == 0.0) {
        m_p[0][1] = -world_h_2;
        m_p[1][1] = world_h_2;
        m_p[0][0] = m_p[1][0] = -d/m_normal[0];
    } else {
        m_p[0][0] = -world_w_2;
        m_p[0][1] = (m_normal[0] * (m_p[0][0]) + d) / (-m_normal[1]);
        m_p[1][0] = world_w_2;
        m_p[1][1] = (m_normal[0] * (m_p[1][0]) + d) / (-m_normal[1]);

    }
    LOG(1, "edge points: " << m_p[0] << " " << m_p[1]);
    c->translate_inside(m_p[0], coord::TO_SCREEN);
    c->translate_inside(m_p[1], coord::TO_SCREEN);
    LOG(1, "translated edge points: " << m_p[0] << " " << m_p[1]);
}

plane::~plane()
{

}

vector_t & 
plane::get_normal()
{
	return m_normal;
}

void 
plane::draw(sys::gfx * gfx, coord * c) 
{
#if 0
    sys::gfx_SDL * g = dynamic_cast<sys::gfx_SDL*>(gfx);
    SDL_Surface * surf = g->get_ctx();
    lineColor(surf, m_p[0][0], m_p[0][1], m_p[1][0], m_p[1][1], m_color.get_value());
#endif
}


