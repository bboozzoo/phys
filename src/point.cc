#include "world.h"
#include "point.h"
#include "log.h"


point::point(world * w, double mass, double x, double y, double z)
    : sphere(w, mass, 1.0, x, y, z)
{
    LOG(1, "creating point");
}


point::~point()
{
}


