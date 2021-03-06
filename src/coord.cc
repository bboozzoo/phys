#include <SDL/SDL_gfxPrimitives.h>
#include "coord.h"
#include "gfx_sdl.h"
#include "log.h"

coord::coord()
    : m_width(0), m_height(0), m_sc_width(0), m_sc_height(0),
      m_offs(2)
{
}

coord::~coord()
{
}

void
coord::init(double width, double height, double sc_width, double sc_height)
{
    m_width = width;
    m_height = height;
    LOG(3, "initializing, w: " << width << " h: " << height);
    m_offs(0) = sc_width / 2.0;
    m_offs(1) = -sc_height / 2.0;
    LOG(3, "offs: " << m_offs);
}

pos_t
coord::translate(pos_t & v, translation_type_t type)
{
    pos_t ret(v.size());
    if (type == TO_SCREEN)
    {
        ret = v + m_offs;
        ret(1) = -ret(1);
    }
    else 
    {
        ret = v - m_offs;
        ret(1) -= 2*v(1);
    }
    return ret;
}

void
coord::translate_inside(pos_t & v, translation_type_t type) 
{
    LOG(3, "transl, point: " << v << " offs: " << m_offs);
    if (v.size() != m_offs.size())
        v.resize(m_offs.size(), true);
    if (type == TO_SCREEN) 
    {
        v += m_offs;
        v(1) = -v(1);
    } 
    else 
    {
        v(1) = -v(1);
        v -= m_offs;
    }
}

void
coord::draw(sys::gfx * g, coord * c) 
{
    if (c != this) {
        LOG(1, "coordinate system mismatch");
        return;
    }
    hline(g);
    vline(g);
}

void
coord::hline(sys::gfx * g)
{
    pos_t point1(2);
    pos_t point2(2);
    int32_t i = 0;

    point1(0) = -m_width / 2.0;
    point1(1) = 0;
    point2(0) = m_width / 2.0;
    point2(1) = 0;
    line(g, point1, point2, LINE_H);

    i = -(((uint32_t)(m_width / 2.0)) / 20) * 20;
    for (; i < m_width / 2.0; i += 20)
    {
        point1(0) = i;
        point2(0) = i;
        point1(1) = 5;
        point2(1) = -5;
        line(g, point1, point2, LINE_V);
    }

}

void
coord::vline(sys::gfx * g) 
{
    pos_t point1(2);
    pos_t point2(2);
    int32_t i = 0;

    point1(0) = 0;
    point1(1) = m_height/2.0;
    point2(0) = 0;
    point2(1) = -m_height/2.0;
    line(g, point1, point2, LINE_V);
    i = -(((uint32_t)(m_width / 2.0)) / 20) * 20;
    for (; i < m_width / 2.0; i += 20)
    {
        point1(0) = -5;
        point2(0) = 5;
        point1(1) = i;
        point2(1) = i;
        line(g, point1, point2, LINE_H);
    }
}

void 
coord::ticks(sys::gfx * g) 
{
/*
    ublas::vector<double> point1(2);
    ublas::vector<double> point2(2);

    point1(0) = 0;
    point1(1) = m_height/2.0;
    point2(0) = 0;
    point2(1) = -m_height/2.0;
    vlineColor(surf, point1(0), point1(1), point2(1), 0xffffffff);
*/
}

void 
coord::line(sys::gfx * g, vertex_t & start, vertex_t & end, line_type_t t)
{
    try 
    {
        sys::gfx_SDL * gf = dynamic_cast<sys::gfx_SDL*>(g);
        SDL_Surface * surf = gf->get_ctx();  
        LOG(4, "line " << ((t == LINE_H) ? "H" : "V") << " before start: " << start << " point 2: " << end);
        translate_inside(start);
        translate_inside(end);
        LOG(4, "line after start: " << start << " point 2: " << end);
        if (t == LINE_H)
            hlineColor(surf, start(0), end(0), start(1), 0x55555555);
        else
            vlineColor(surf, start(0), start(1), end(1), 0x55555555);
    }
    catch (std::bad_cast & b)
    {
        std::cerr << "exception " << b.what() << std::endl;
    }
}

bool
coord::visible(pos_t & v) 
{
    /* 2D only */
    LOG(2, "check visible vector/point: " << v << "in screen: " << m_width << "x" << m_height);
    if (v(0) <= (m_width / 2.0) && v(0) >= (-m_width / 2.0) &&
        v(1) <= (m_height / 2.0) && v(1) >= (-m_height / 2.0))
        return true;
    return false;
}

void
coord::get_dimensions(dimensions_t & world_dim, dimensions_t & screen_dim)
{
    if (world_dim.size() < 2)
        world_dim.resize(2);
    if (screen_dim.size() < 2)
        screen_dim.resize(2);
    world_dim[0] = m_width;
    world_dim[1] = m_height;
    screen_dim[0] = m_sc_width;
    screen_dim[1] = m_sc_height;
}

