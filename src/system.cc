#include <cstdlib>
#include <exception>
#include <iostream>
#include "system.h"
#include "gfx_sdl.h"
#include "input_sdl.h"
#include "log.h"

namespace phys 
{

system::sys_info * system::m_sys_info = NULL;

void system::init(uint32_t sys_init_flags) 
{
    try
    {
        LOG(1, "init sys info");
        if (m_sys_info == NULL)
            m_sys_info = new sys_info;

        if (sys_init_flags & INIT_GFX) 
        {
            LOG(1, "init GFX");
            m_sys_info->m_gfx = new gfx_SDL();
            m_sys_info->m_gfx->init();
        }

        if (sys_init_flags & INIT_INPUT) 
        {
            LOG(1, "init input");
            m_sys_info->m_input = new input_SDL();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "exception" << e.what() << std::endl;
        throw;
    }
}

void system::finish() 
{
    LOG(1, "sys info? " << (void *) m_sys_info);
	if (m_sys_info != NULL)
    {
		if (m_sys_info->m_gfx != NULL) 
        {
            LOG(1, "cleanup GFX");
			delete m_sys_info->m_gfx;
        }
        if (m_sys_info->m_input != NULL)
        {
            LOG(1, "cleanup input");
            delete m_sys_info->m_input;
        }
        delete m_sys_info;
    }
    /* TODO: call SDL_Quit somewhere */
    SDL_Quit();
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

