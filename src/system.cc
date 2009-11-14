#include <cstdlib>
#include <exception>
#include <iostream>
#include "system.h"
#include "gfx_sdl.h"
#include "input_sdl.h"
#include "log.h"

namespace sys
{

system * system::m_sys_single = NULL;

system::system(uint32_t sys_init_flags) 
{
    try
    {
        LOG(1, "init sys info");
        if (sys_init_flags & INIT_GFX) 
        {
            LOG(1, "init GFX");
            m_gfx = new gfx_SDL();
            m_gfx->init();
        }

        if (sys_init_flags & INIT_INPUT) 
        {
            LOG(1, "init input");
            m_input = new input_SDL();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "exception" << e.what() << std::endl;
        throw;
    }
}

system::~system()
{

}

system * system::init(uint32_t sys_init_flags) 
{
    system * s = NULL;
    try
    {
        if (m_sys_single == NULL)
        {
            s = new system(sys_init_flags);
            m_sys_single = s;
        } 
        else
            s = m_sys_single;
    }
    catch (std::exception &e)
    {
        std::cerr << "exception" << e.what() << std::endl;
        throw;
    }
    return s;
}

void system::finish() 
{
    LOG(1, "sys info? " << (void *) m_sys_single);
	if (m_sys_single != NULL)
    {
		if (m_sys_single->m_gfx != NULL) 
        {
            LOG(1, "cleanup GFX");
			delete m_sys_single->m_gfx;
        }
        if (m_sys_single->m_input != NULL)
        {
            LOG(1, "cleanup input");
            delete m_sys_single->m_input;
        }
        SDL_Quit();
        delete m_sys_single;
        m_sys_single = NULL;
    }
}

gfx * system::get_gfx()
{
    return m_sys_single->m_gfx;
}

input * system::get_input()
{
    return m_sys_single->m_input;
}

}

