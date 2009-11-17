#include <sstream>
#include "gfx.h"
#include "log.h"

namespace sys
{

color::color(uint32_t col)
    : m_color(col)
{

}

color::~color()
{
}

uint32_t
color::get_value()
{
    return m_color;
}

std::string
color::to_str()
{
    std::stringstream os;
    os << "0x";
    os.width(8);
    os.fill('0');
    os << std::hex << m_color;
    return os.str();
}

}
