#include <SDL/SDL_gfxPrimitives.h>
#include "world.h"
#include "box.h"
#include "gfx_sdl.h"
#include "log.h"

box::box(world * w, double mass, double width, double height, double x, double y, double z)
    : object_phys(w, object::BOX)
{
    pos_t p(3);
    p[0] = x;
    p[1] = y;
    p[2] = z;

    dimensions_t d(3);
    d[0] = width;
    d[1] = height;
    d[2] = 1;

    double volume = width * height * 1.0;
    double density = mass / volume;
    LOG(1, "creating box mass: " << mass << " vol: " << volume << " density: " << density << " pos: " << p);
    set_geometry(d);
    set_position(p);
    set_density(density);
}

box::~box()
{

}

void 
box::draw(sys::gfx * gfx, coord * c)
{
    sys::gfx_SDL * g = dynamic_cast<sys::gfx_SDL*>(gfx);
    SDL_Surface * surf = g->get_ctx();
    pos_t v(3);
    dimensions_t d(3);
    get_position(v);
    get_geometry(d);
    d[0] /= 2.0;
    d[1] /= 2.0;
    c->translate_inside(v, coord::TO_SCREEN);
    boxColor(surf, v[0] - d[0], v[1] - d[1], v[0] + d[0], v[1] + d[1], m_color.get_value());
}


