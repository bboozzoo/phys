#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "system.h"
#include "sim.h"
#include "plane.h"
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
        ublas::vector<double> force(3);
        ublas::vector<double> & pos = p->get_pos();
	ublas::vector<double> & plane_p = m_plane.get_p();
	ublas::vector<double> tmp_pos(3);
	ublas::vector<double> tmp(3);
	ublas::vector<double> acc(3);
	LOG(2, "p: " << pos);
	LOG(2, "v: " << vel);
	for (int i = 0 ; i < 3; i++)
		force(i) = 0;
	apply_gravity(p, force);

	tmp_pos = pos + (vel * delta_ms);

	tmp = tmp_pos - plane_p;
	double prod = ublas::inner_prod(tmp, m_plane.get_normal());
	LOG(1, "tmp_pos: " << pos << " tmp: " << tmp << " prod: " << prod);
	if (prod < 1.0) /* collision */
	{
		ublas::vector<double> vn(3);
		ublas::vector<double> vt(3);
		double len_vn;
		LOG(1, "got collision");
		LOG(1, "v: " << vel);
		vn = ublas::inner_prod(vel, m_plane.get_normal()) * (m_plane.get_normal());
		len_vn = norm_2(vn);
		LOG(1, "len vn: " << len_vn);
		if (len_vn < 0.1)
		{
			LOG(1, "normal small");
			for (int i = 0; i < vn.size(); i++)
				vn(i) = 0;
		}
		LOG(1, "vn: " << vn);
		vt = vel - vn;
		LOG(1, "vt: " << vt);
		vel = vt - 0.8 * vn;
		LOG(1, "vel: " << vel);
		LOG(1, "pos: " << pos);
    	} 
	else /* no collision */
	{
		pos = tmp_pos;	
		acc = force * p->get_1_over_mass();
		LOG(2, "a: " << acc);
		vel += acc * delta_ms;
		LOG(2, "v: " << vel << " f: " << force << " p: " << pos);
	}
    }
}

void
simulation::apply_gravity(point * p, ublas::vector<double> & f)
{
    f += p->get_mass() * m_accel_gravity;
    LOG(1, "appply gravity, g: " << m_accel_gravity << " f: " << f << " m: " << p->get_mass());
}

void 
simulation::setup()
{
    point * p = NULL;

    p = new point(0.1, 250, -280, 0);
    if (p != NULL) 
    {
        ublas::vector<double> & v = p->get_velocity();
	v(0) = -10;
        m_points.push_back(p);
    }
    
    p = new point(100, -250, -180, 0);
    if (p != NULL) 
    {
        ublas::vector<double> & v = p->get_velocity();
        v(0) = 5;
        v(1) = 10;
        m_points.push_back(p);
    }
    ublas::vector<double> p1(3);
    p1(0) = -400;
    p1(1) = -300;
    p1(2) = 0;
    ublas::vector<double> p2(3);
    p2(0) = 400;
    p2(1) = -300;
    p2(2) = 0;

    LOG(1, "creating plane, p1: " << p1 << " p2: " << p2);
    m_plane.init(p1, p2);

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
