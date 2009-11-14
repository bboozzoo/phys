#include "world_gfx.h"

world_gfx::world_gfx()
{

}

world_gfx::~world_gfx()
{
    /* delete all objects from list */
}

void
world_gfx::draw(sys::gfx * gfx, coord * c)
{
    std::list<drawable *>::iterator it;
    for (it = m_gobjects.begin(); it != m_gobjects.end(); it++)
        (*it)->draw(gfx, c);

}

void
world_gfx::add(drawable * og) 
{
    m_gobjects.push_back(og);
}
