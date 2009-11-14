#include "world.h"
#include "log.h"
#include "point.h"

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
    LOG(2, "draw");
    world_gfx::draw(gfx, m_coord);
}

void
world::setup()
{
    LOG(1, "world setup");
    /* static configuration */
    point * p = new point(this, 1, 0, 0, 0);
    world_gfx::add(p);
    world_phys::add(p);
}

