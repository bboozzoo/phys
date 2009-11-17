#include <SDL/SDL_gfxPrimitives.h>
#include "sphere.h"
#include "world.h"
#include "log.h"
#include "gfx_sdl.h"

sphere::sphere(world * w, double mass, double radius, double x, double y, double z)
    : object_phys(w, object::SPHERE), m_radius(radius)
{
    pos_t p(3);
    p(0) = x;
    p(1) = y;
    p(2) = z;

    dimensions_t d(1);
    d[0] = radius;

    double volume = 4.0/3.0 * M_PI * radius * radius * radius;
    double density = mass / volume;
    LOG(1, "creating sphere mass: " << mass << " vol: " << volume << " density: " << density << " pos: " << p);
    set_geometry(d);
    set_position(p);
    set_density(density);
}

sphere::~sphere()
{

}

void
sphere::draw(sys::gfx * gfx, coord * c)
{
    sys::gfx_SDL * g = dynamic_cast<sys::gfx_SDL*>(gfx);
    SDL_Surface * surf = g->get_ctx();
//    uint32_t col = (get_in_collision() == true) ? sys::color::ORANGE : m_color.get_value();
    pos_t v(3);
    get_position(v);
    c->translate_inside(v, coord::TO_SCREEN);
    filledCircleColor(surf, v(0), v(1), m_radius, m_color.get_value());
//    set_in_collision(false);
}

