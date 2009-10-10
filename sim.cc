#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "system.h"
#include "sim.h"
#include "gfx_sdl.h"

namespace phys
{

void 
simulation::run()
{

    uint32_t t_delta = 0;
    initialize();

    while(true)
    {
        uint32_t ev = 0;
        uint32_t now = 0;
        ev = m_input->poll();
        if (ev == -1)
            break;
        now = SDL_GetTicks();
        t_delta = now - m_time;
        if (t_delta > 1) 
        {
            calc();
            draw();
            m_gfx->update();
        }
    }

}

void 
simulation::initialize() 
{
    double width = 0;
    double height = 0;
    m_input = system::get_input();
    m_gfx = system::get_gfx();
    m_time = SDL_GetTicks();

    width = m_gfx->get_width();
    height = m_gfx->get_height();
    m_coord.init(width, height, width, height);
}

void 
simulation::draw() 
{
    gfx_SDL * g = dynamic_cast<gfx_SDL*>(m_gfx);
    SDL_Surface * surf = NULL;
    std::list<point*>::iterator it; 
    if (g == NULL)
        return;

    m_coord.draw(m_gfx);
    surf = g->get_ctx();
    for (it = m_points.begin(); it != m_points.end(); it++)
    {
        ublas::vector<double> v ((*it)->get_pos());
        m_coord.translate_inside(v);
        filledCircleColor(surf, v(0), v(1), 10, 0xffffffff);
    }
    /*
    filledCircleColor(surf, 100, 100, 10, 0xffffffff);
    filledCircleColor(surf, 0, 0, 10, 0xffffffff);
    filledCircleColor(surf, 640, 480, 10, 0xffffffff);
    */
}

void 
simulation::calc() 
{
    std::list<point*>::iterator it;
    for (it = m_points.begin(); it != m_points.end(); it++)
    {
        
    }
}

void 
simulation::setup()
{
    point * p = NULL;

    p = new point(10, 200, 100, 0);
    if (p != NULL)
        m_points.push_back(p);
}

void simulation::finish() 
{
    while (!m_points.empty())
    {
        std::list<point*>::iterator it = m_points.begin();
        delete (*it);
        m_points.erase(it);
    }
}

}
