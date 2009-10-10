#include <SDL/SDL_gfxPrimitives.h>
#include <boost/numeric/ublas/io.hpp>
#include "coord.h"
#include "gfx_sdl.h"
#include "log.h"

namespace phys
{
    
coord::coord()
    : m_width(0), m_height(0), m_sc_width(0), m_sc_height(0),
      m_offs(3)
{
}

coord::~coord()
{
}

void
coord::init(double width, double height, double sc_width, double sc_height)
{
    LOG("initializing, w: " << width << " h: " << height);
    m_offs(0) = sc_width / 2.0;
    m_offs(1) = sc_height / 2.0;
    m_offs(2) = 0;
    LOG("offs: " << m_offs);
}


ublas::vector<double> 
coord::translate(ublas::vector<double> & v)
{
    ublas::vector<double> ret(v.size());
    ret = v + m_offs;
    ret(0) -= v(0);
    return ret;
}

void
coord::translate_inside(ublas::vector<double> & v) 
{
    double old_x = v(0);
    if (v.size() != m_offs.size())
        v.resize(m_offs.size(), true);
    v += m_offs;
    v(0) -= old_x;
}

void
coord::draw(gfx * g) 
{
    gfx_SDL * gf = dynamic_cast<gfx_SDL*>(g);
    SDL_Surface * surf = gf->get_ctx();  
    ublas::vector<double> point1(2);
    ublas::vector<double> point2(2);
    point1(0) = -m_width/2.0;
    point1(1) = 0;
    point2(0) = m_width/2.0;
    point2(1) = 0;
    translate_inside(point1);
    translate_inside(point2);
    hlineColor(surf, point1(0), point2(0), point1(1), 0xffffffff);
    point1(0) = 0;
    point1(1) = m_height/2.0;
    point2(0) = 0;
    point2(1) = -m_height/2.0;
    translate_inside(point1);
    translate_inside(point2);
    vlineColor(surf, point1(0), point1(1), point2(1), 0xffffffff);

}

}
