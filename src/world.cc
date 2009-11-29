#include "world.h"
#include "log.h"
#include "sphere.h"
#include "box.h"
#include "plane.h"

world::world(coord & coord_sys)
    : world_phys(), world_gfx(), m_coord(&coord_sys)
{
    LOG(1, "creating world");
}
world::~world()
{
    LOG(1, "destroying world");
}

void 
world::advance(double delta_t)
{
    LOG(2, "advance by: " << delta_t << "s");
    world_phys::advance(delta_t);
}

void 
world::draw(sys::gfx * gfx)
{
    LOG(3, "draw");
    world_gfx::draw(gfx, m_coord);
}

void
world::setup()
{
    LOG(1, "world setup");
#if 0
    /* static configuration */
    for (int i = 0; i < 5; i++) {
        sys::color col(sys::color::BLUE);
        sphere * p = new sphere(this, 50, 5, (double) (i % 10) * 11.0 , -100 + (i % 10) * 10, 0);
        p->set_color(col);
        world_gfx::add(p);
        world_phys::add(p);
    }
    for (int i = 0; i < 5; i++) {
        sys::color col(sys::color::WHITE);
        sphere * p = new sphere(this, 0.005, 5, 5 + (double) (i % 10) * 11.0 , -50 + (i % 10) * 10, 0);
        p->set_color(col);
        world_gfx::add(p);
        world_phys::add(p);
    }
    for (int i = 0; i < 5; i++) {
        sys::color col(sys::color::GREEN);
        sphere * p = new sphere(this, 150, 5, (double) (i % 10) * 11.0 , 0 + (i % 10) * 10, 0);
        p->set_color(col);
        world_gfx::add(p);
        world_phys::add(p);
    }
#endif
#if 1
    {
        for (int i = 0; i < 12; i++) {
            sys::color col(sys::color::ORANGE);
            box * b = new box(this, 0.005, 5, 20, 150 + i * 2, -100 + i * 25, 0);
            b->set_color(col);
            world_gfx::add(b);
            world_phys::add(b);
        }
    }
#endif
    sys::color col(sys::color::RED);
    vertex_t n(3);
    plane * pl;
#if 1
    n[0] = 0;
    n[1] = 1;
    n[2] = 0;
    pl = new plane(this, n, 299);
    pl->set_color(col);
    world_gfx::add(pl);
    world_phys::add(pl);
#endif
#if 1
    n[0] = 1;
    n[1] = 0;
    n[2] = 0;
    pl = new plane(this, n, 399);
    pl->set_color(col);
    world_gfx::add(pl);
    world_phys::add(pl);
#endif
#if 1
    n[0] = -1;
    n[1] = 0;
    n[2] = 0;
    pl = new plane(this, n, 399);
    pl->set_color(col);
    world_gfx::add(pl);
    world_phys::add(pl);
#endif
}

