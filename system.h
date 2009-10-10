#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#include <cstdint>
#include "gfx.h"

namespace phys 
{

class system 
{
	public:
		enum 
		{
			INIT_GFX,
			INIT_AUDIO,
		};

		static void init(uint32_t sys_init_flags);
		static void finish();
	private:
		system();
		~system();
	
		struct sys_info 
		{
			gfx * m_gfx;	
		};
		
		static sys_info * m_sys_info;
	
};

}
#endif /* __SYSTEM_H__ */
