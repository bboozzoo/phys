#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "system.h"
#include "sim.h"
#include "plane.h"
#include "gfx_sdl.h"
#include "event.h"
#include "log.h"

namespace phys
{

simulation::simulation(gfx * g, input * i)
    : m_gfx(g), m_input(i), m_accel_gravity(2)
{
    double width = 0;
    double height = 0;
    width = m_gfx->get_width();
    height = m_gfx->get_height();
    m_coord.init(width, height, width, height);

    m_accel_gravity(0) = 0.0;
    m_accel_gravity(1) = -9.81;
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
        event ev;
        double now = 0;

        m_input->poll(ev);
        if (ev == event::EVENT_QUIT)
            break;

        now = ((double)SDL_GetTicks()) / 1000.0;
        t_delta = now - m_time;
        LOG(2, "delta: : " << t_delta << "ms, now: " << now << "ms, prev: " << m_time << "ms");

        if (t_delta >= 0.001) 
        {
            LOG(2, "--- update ---");
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
    try 
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
        ublas::vector<double> p1 = m_plane.get_p1();
        ublas::vector<double> p2 = m_plane.get_p2();
        m_coord.translate_inside(p1);
        m_coord.translate_inside(p2);
        lineColor(surf, p1(0), p1(1), p2(0), p2(1), 0xff0000ff);
        /*
        filledCircleColor(surf, 100, 100, 10, 0xffffffff);
        filledCircleColor(surf, 0, 0, 10, 0xffffffff);
        filledCircleColor(surf, 640, 480, 10, 0xffffffff);
        */
    } 
    catch (std::bad_cast & b)
    {
        std::cerr << "exception " << b.what() << std::endl;
        throw;
    }
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
        ublas::vector<double> force(2);
        ublas::vector<double> & pos = p->get_pos();
        ublas::vector<double> tmp_pos(2);
        ublas::vector<double> tmp(2);
        ublas::vector<double> acc(2);
        LOG(2, "p: " << pos);
        LOG(2, "v: " << vel);
        for (int i = 0 ; i < 2; i++)
            force(i) = 0;
        apply_gravity(p, force);

        tmp_pos = pos + (vel * delta_ms);

        bool inside = m_plane.is_inside(tmp_pos);
        double distance = 0;
        if (inside)
            distance = ublas::inner_prod(tmp_pos, m_plane.get_nn()) + m_plane.get_p();
        LOG(2, "tmp_pos: " << tmp_pos << " pos: " << pos << " prod: " << distance);
        if (inside == true && std::abs(distance) < 1.0) /* collision */
        {
            ublas::vector<double> vn(2);
            ublas::vector<double> vt(2);
            double len_vn;
            LOG(2, "got collision");
            LOG(2, "v: " << vel);
            vn = ublas::inner_prod(vel, m_plane.get_nn()) * (m_plane.get_nn());
            len_vn = norm_2(vn);
            LOG(2, "len vn: " << len_vn);
            if (len_vn < 0.1)
            {
                LOG(1, "normal small");
                for (size_t i = 0; i < vn.size(); i++)
                    vn(i) = 0;
            }
            LOG(2, "vn: " << vn);
            vt = vel - vn;
            LOG(2, "vt: " << vt);
            vel = vt - 0.8 * vn;
            LOG(2, "vel: " << vel);
            LOG(2, "pos: " << pos);
        } 
        else /* no collision */
        {
            pos = tmp_pos;	
            acc = force * p->get_1_over_mass();
            LOG(3, "a: " << acc);
            vel += acc * delta_ms;
            LOG(3, "v: " << vel << " f: " << force << " p: " << pos);
        }
    }
}

void
simulation::apply_gravity(point * p, ublas::vector<double> & f)
{
    f += p->get_mass() * m_accel_gravity;
    LOG(2, "appply gravity, g: " << m_accel_gravity << " f: " << f << " m: " << p->get_mass());
}

void 
simulation::setup()
{
    try
    {
        point * p = NULL;

        p = new point(0.1, 100, 0);
        ublas::vector<double> & v1 = p->get_velocity();
        v1(0) = -10;
        m_points.push_back(p);

        p = new point(100, 0, 50);
        ublas::vector<double> & v2 = p->get_velocity();
    /*        v(0) = 5;
        v(1) = 10;*/
        m_points.push_back(p);
        ublas::vector<double> p1(2);
        p1(0) = -100;
        p1(1) = -0;
        ublas::vector<double> p2(2);
        p2(0) = 200;
        p2(1) = -50;

        LOG(1, "creating plane, p1: " << p1 << " p2: " << p2);
        m_plane.init(p1, p2);
    } 
    catch (std::exception &e) 
    {
        std::cerr << "exception" << e.what() << std::endl;
        throw;
    }   

}

void 
simulation::finish() 
{
    while (!m_points.empty())
    {
        std::list<point*>::iterator it = m_points.begin();
        delete (*it);
        m_points.erase(it);
    }
}

}
