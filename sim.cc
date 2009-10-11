#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "system.h"
#include "sim.h"
#include "gfx_sdl.h"
#include "log.h"

namespace phys
{

simulation::simulation(gfx * g, input * i)
    : m_gfx(g), m_input(i), m_accel_gravity(3)
{
    double width = 0;
    double height = 0;
    width = m_gfx->get_width();
    height = m_gfx->get_height();
    m_coord.init(width, height, width, height);

    m_accel_gravity(0) = 0.0;
    m_accel_gravity(1) = -9.81;
    m_accel_gravity(2) = 0.0;
    LOG(1, "initialize, g: " << m_accel_gravity);
}

simulation::~simulation() 
{

}

void 
simulation::run()
{

    double t_delta = 0;
    m_time = ((double) SDL_GetTicks()) / 1000.0;

    while(true)
    {
        uint32_t ev = 0;
        double now = 0;
        ev = m_input->poll();
        if (ev == -1)
            break;
        now = ((double)SDL_GetTicks()) / 1000.0;
        t_delta = now - m_time;
        LOG(1, "delta: : " << t_delta << "ms, now: " << now << "ms, prev: " << m_time << "ms");
        if (t_delta >= 0.001) 
        {
            LOG(1, "--- update ---");
            calc(t_delta);
            m_time = now;
        }
        draw();
        m_gfx->update();
    }

}

void 
simulation::draw() 
{
    gfx_SDL * g = dynamic_cast<gfx_SDL*>(m_gfx);
    SDL_Surface * surf = NULL;
    std::list<point*>::iterator it; 
    if (g == NULL)
        return;

    surf = g->get_ctx();
    boxColor(surf, 0, 0, surf->w - 1, surf->h - 1, 0x000000ff);
    m_coord.draw(m_gfx);
    for (it = m_points.begin(); it != m_points.end(); it++)
    {
        ublas::vector<double> v ((*it)->get_pos());
        m_coord.translate_inside(v);
        filledCircleColor(surf, v(0), v(1), 1, 0xffffffff);
    }
    /*
    filledCircleColor(surf, 100, 100, 10, 0xffffffff);
    filledCircleColor(surf, 0, 0, 10, 0xffffffff);
    filledCircleColor(surf, 640, 480, 10, 0xffffffff);
    */
}

void 
simulation::calc(double delta_ms) 
{
    std::list<point*>::iterator it;
    LOG(2, "delta: " << delta_ms);
    for (it = m_points.begin(); it != m_points.end(); it++)
    {
        point * p = (*it);
        ublas::vector<double> & vel = p->get_velocity();
        ublas::vector<double> & force = p->get_force();
        ublas::vector<double> & pos = p->get_pos();
        ublas::vector<double> acc(3);
        LOG(2, "f: " << force);
        LOG(2, "p: " << pos);
        LOG(2, "v: " << vel);
        acc = force * p->get_1_over_mass();
        LOG(2, "a: " << acc);
        pos += vel * delta_ms;
        vel += acc * delta_ms;
        LOG(2, "v: " << vel << " f: " << force << " p: " << pos);
        if (!m_coord.visible(pos))
            exit(1);
    }
}

void
simulation::apply_gravity(point * p)
{
    ublas::vector<double> & force = p->get_force();
    force = p->get_mass() * m_accel_gravity;
    LOG(1, "appply gravity, g: " << m_accel_gravity << " f: " << force << " m: " << p->get_mass());
}

void 
simulation::setup()
{
    point * p = NULL;

    p = new point(0.1, 0, 300, 0);
    if (p != NULL) 
    {
        apply_gravity(p);
        m_points.push_back(p);
    }
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
