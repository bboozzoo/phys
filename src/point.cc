#include <SDL/SDL_gfxPrimitives.h>
#include "world.h"
#include "point.h"
#include "log.h"
#include "conf.h"
#include "gfx_sdl.h"


point::point(world * w, double mass, double x, double y, double z)
    : object_phys(w, object::SPHERE)
{
    pos_t p(3);
    p(0) = x;
    p(1) = y;
    p(2) = z;

    LOG(1, "creating point mass: " << mass << " pos: " << p);
    dimensions_t d(1);
    d[0] = 1.0;
    set_geometry(d);
    set_position(p);
    set_density(DENSITY);
}


point::~point()
{
}

void
point::draw(sys::gfx * gfx, coord * c)
{
    sys::gfx_SDL * g = dynamic_cast<sys::gfx_SDL*>(gfx);
    SDL_Surface * surf = g->get_ctx();
    pos_t v(3);
    get_position(v);
    c->translate_inside(v, coord::TO_SCREEN);
    filledCircleColor(surf, v(0), v(1), 1, sys::color::WHITE);
}

