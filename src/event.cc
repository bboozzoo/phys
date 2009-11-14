#include <cstdlib>
#include "event.h"


event::event()
    : m_type(NONE)
{
}

event::~event()
{
}

event::event(const event & e)
{
    m_info = e.m_info;
    m_type = e.m_type;
}

event_info & 
event::get_info()
{
    return *m_info;
}

bool 
event::operator==(event_type_t etype)
{
    if (m_type == etype)
        return true;
    return false;
}

event::event_type_t
event::get_type() 
{
    return m_type;
}

void 
event::set_type(event_type_t e)
{
    m_type = e;
}

void 
event::set_info(event_info_sh_t & e)
{
    m_info = e;
}

void 
event::clear()
{
    m_info.reset();
    m_type = NONE;
}



