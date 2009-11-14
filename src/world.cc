#include "world.h"
#include "log.h"
#include "point.h"
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
    /* static configuration */
    for (int i = 0; i < 10; i++) {
        point * p = new point(this, 1, 0 + (double) (i % 400)/2.0, -200 + (i % 400), 0);
        world_gfx::add(p);
        world_phys::add(p);
    }

    vertex_t n(3);
    plane * pl;
#if 1
    n[0] = 0;
    n[1] = 1;
    n[2] = 0;
    pl = new plane(this, n, 299);
    world_gfx::add(pl);
    world_phys::add(pl);
#endif
#if 1
    n[0] = 1;
    n[1] = 0;
    n[2] = 0;
    pl = new plane(this, n, 399);
    world_gfx::add(pl);
    world_phys::add(pl);
#endif
#if 1
    n[0] = -1;
    n[1] = 0;
    n[2] = 0;
    pl = new plane(this, n, 399);
    world_gfx::add(pl);
    world_phys::add(pl);
#endif
}

