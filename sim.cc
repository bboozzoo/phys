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
    m_bin_set.init(width / 10.0, height / 10.0, width, height);

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

    m_state.m_run = true;
    /* init time */
    m_time = ((double) SDL_GetTicks()) / 1000.0;
    
    while(m_state.m_run)
    {
        double now = 0;

        handle_input();

        now = ((double)SDL_GetTicks()) / 1000.0;
        t_delta = now - m_time;
        LOG(2, "delta: : " << t_delta << "ms, now: " << now << "ms, prev: " << m_time << "ms");

        if (t_delta >= 0.001) 
        {
            if (!m_state.m_paused) 
            {
                LOG(2, "--- update ---");
                /* temporary fix for t_delta too large */
                while (t_delta > 0.01)
                {
                    calc(0.005);
                    t_delta -= 0.005;
                }
                calc(t_delta);
            }
            m_time = now;
        }
        draw();
        m_gfx->update();
    }

}

void
simulation::handle_input()
{
    event ev;

    m_input->poll(ev);
    switch(ev.get_type())
    {
        case event::QUIT:
            m_state.m_run = false;
            break;
        case event::MOUSE_BUTTON_DOWN: 
            LOG(1, "down");
        case event::MOUSE_BUTTON_UP:
            {
                LOG(1, "mouse button event " << ((ev == event::MOUSE_BUTTON_DOWN) ? "down" : "up") <<  " p: " << m_input_state.m_last_click_pos << " valid: " << m_input_state.m_last_click_valid);
                pos_t p(2);
                try
                {
                    event_info_mouse & m = dynamic_cast<event_info_mouse &>(ev.get_info());
                    p(0) = m(0);
                    p(1) = m(1);
                    m_coord.translate_inside(p, coord::FROM_SCREEN);
                    LOG(1, "COORDS: " << p);
                    if (ev == event::MOUSE_BUTTON_DOWN)
                    {
                        m_input_state.m_last_click_valid = true;
                        m_input_state.m_last_click_pos = p;
                    }
                    else if (m_input_state.m_last_click_valid == true)
                    {
                        vector_t initial_velocity = p - m_input_state.m_last_click_pos;
                        add_point(m_input_state.m_last_click_pos, initial_velocity);
                        m_input_state.m_last_click_valid = false;
                    }
                }
                catch (std::bad_cast & b) 
                {
                    std::cerr << "event info mouse, bad cast: " << b.what() << std::endl;
                }

                break;
            }
        case event::KEY:
            {
                LOG(1, "key event");
                try
                {
                    event_info_key & k = dynamic_cast<event_info_key &>(ev.get_info());
                    switch (k.get_key())
                    {
                        case event_info_key::SPACE:
                            m_state.m_paused = !m_state.m_paused;
                            break;
                        case event_info_key::Q:
                            m_state.m_run = false;
                            break;
                        default:
                            break;
                    }
                }
                catch (std::bad_cast & b)
                {
                    std::cerr << "event info key, bad cast: " << b.what() << std::endl;
                }
                break;
            }
        default:
            break;
    }

}

void 
simulation::draw() 
{
    gfx_SDL * g = dynamic_cast<gfx_SDL*>(m_gfx);
    if (g == NULL)
        return;

    SDL_Surface * surf = NULL;
    std::list<point*>::iterator it; 
    if (g == NULL)
        return;

    surf = g->get_ctx();
    boxColor(surf, 0, 0, surf->w - 1, surf->h - 1, color::BLACK);
    m_coord.draw(m_gfx);
    for (it = m_points.begin(); it != m_points.end(); it++)
    {
        pos_t v ((*it)->get_pos());
        m_coord.translate_inside(v, coord::TO_SCREEN);
        filledCircleColor(surf, v(0), v(1), 1, color::WHITE);
    }
    vertex_t p1 = m_plane.get_p1();
    vertex_t p2 = m_plane.get_p2();
    m_coord.translate_inside(p1, coord::TO_SCREEN);
    m_coord.translate_inside(p2, coord::TO_SCREEN);
    lineColor(surf, p1(0), p1(1), p2(0), p2(1), color::RED);

    /*
       filledCircleColor(surf, 100, 100, 10, 0xffffffff);
       filledCircleColor(surf, 0, 0, 10, 0xffffffff);
       filledCircleColor(surf, 640, 480, 10, 0xffffffff);
       */

    if (m_state.m_paused)
    {
        stringColor(surf, 0, 10, "** PAUSED **", color::WHITE);
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
        pos_t & pos = p->get_pos();
        if (!m_coord.visible(pos))
        {
            it = m_points.erase(it);
            it--;
            delete p;
            continue;
        }

        vector_t & vel = p->get_velocity();
        vector_t force(2);
        pos_t tmp_pos(2);
        vector_t acc(2);
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
            vector_t vn(2);
            vector_t vt(2);
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
simulation::apply_gravity(point * p, vector_t & f)
{
    f += p->get_mass() * m_accel_gravity;
    LOG(2, "appply gravity, g: " << m_accel_gravity << " f: " << f << " m: " << p->get_mass());
}

void 
simulation::setup()
{
    pos_t pos(2);
    vector_t vel(2);

    pos(0) = 100.0;
    pos(1) = 0.0;
    vel(0) = -10.0;
    vel(1) = 0;

    add_point(pos, vel);

    pos(0) = 0.0; 
    pos(1) = 50.0;
    /*
    vel(0) = 5;
    vel(1) = 10;
    */
    add_point(pos, vel);

    vertex_t p1(2);
    p1(0) = -100;
    p1(1) = -0;
    vertex_t p2(2);
    p2(0) = 200;
    p2(1) = -50;

    LOG(1, "creating plane, p1: " << p1 << " p2: " << p2);
    m_plane.init(p1, p2);

}

void 
simulation::add_point(pos_t & initial_position, vector_t & initial_velocity)
{
    try
    {
        LOG(1, "add point, initial p: " << initial_position << " initial v: " << initial_velocity);
        point * p = new point(0.1, initial_position, initial_velocity);
        m_points.push_back(p);
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
