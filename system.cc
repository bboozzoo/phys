#include <cstdlib>
#include "system.h"
#include "gfx_sdl.h"
#include "input_sdl.h"

namespace phys 
{

system::sys_info * system::m_sys_info = NULL;

void system::init(uint32_t sys_init_flags) 
{
    if (m_sys_info == NULL)
        m_sys_info = new sys_info;
    if (sys_init_flags & INIT_GFX) 
    {
        m_sys_info->m_gfx = new gfx_SDL();
        m_sys_info->m_gfx->init();
    }

    if (sys_init_flags & INIT_INPUT) 
    {
        m_sys_info->m_input = new input_SDL();
    }
}

void system::finish() 
{
	if (m_sys_info != NULL)
    {
		if (m_sys_info->m_gfx != NULL)
			delete m_sys_info->m_gfx;
        if (m_sys_info->m_input != NULL)
            delete m_sys_info->m_input;
    }
    /* TODO: call SDL_Quit somewhere */
}

gfx * system::get_gfx()
{
    return m_sys_info->m_gfx;
}

input * system::get_input()
{
    return m_sys_info->m_input;
}

}

