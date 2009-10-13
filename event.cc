#include "event.h"

namespace phys
{


event::event()
    : m_info(NULL), m_type(EVENT_NONE)
{
}

event::~event()
{
    if (m_info != NULL)
        delete m_info;
}

event::event(const event & e)
{

}

event_info & 
event::get_info()
{

}

bool 
event::operator==(const event & e, event_type_t etype)
{

}

void 
event::set_type(etype e)
{

}

void 
event::set_info(einfo * e)
{

}

void 
event::clear()
{
    if (m_info != NULL)
        delete m_info;
    m_info = NULL;
    m_type = EVENT_NONE:
}


}

