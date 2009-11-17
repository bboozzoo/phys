#include "drawable.h"
#include "log.h"

drawable::drawable(sys::color c)
    : m_color(c)
{
}

drawable::drawable()
    : m_color(sys::color(sys::color::WHITE))
{
}
            
drawable::~drawable()
{

}

void
drawable::set_color(sys::color & c)
{
    LOG(1, "set color to: " << c.to_str());
    m_color = c;
}

