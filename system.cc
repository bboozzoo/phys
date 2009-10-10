#include <cstdlib>
#include "system.h"
#include "gfx_sdl.h"

namespace phys 
{

system::sys_info * system::m_sys_info = NULL;

void system::init(uint32_t sys_init_flags) 
{
	m_sys_info = new sys_info;
	m_sys_info->m_gfx = new gfx_SDL();
	m_sys_info->m_gfx->init();
}

void system::finish() 
{
	if (m_sys_info != NULL)
		if (m_sys_info->m_gfx != NULL)
			delete m_sys_info->m_gfx;
}


}

