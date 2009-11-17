#include "world.h"
#include "box.h"

box::box(world * w, double mass, double x, double y, double z)
    : object_phys(w, object::BOX)
{
     
}

box::~box()
{

}

void 
box::draw(sys::gfx * gfx, coord * c)
{

}


