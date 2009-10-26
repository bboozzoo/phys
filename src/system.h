#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#include <cstdint>
#include "gfx.h"
#include "input.h"

namespace phys 
{

class system 
{
	public:
		enum 
		{
			INIT_GFX    = 0x01,
			INIT_AUDIO  = 0x02,
            INIT_INPUT  = 0x04,
		};

		static void init(uint32_t sys_init_flags);
		static void finish();
        static gfx * get_gfx();
        static input * get_input();
        

	private:
		system();
		~system();
	
		struct sys_info 
		{
			gfx * m_gfx;	
            input * m_input;
		};
		
		static sys_info * m_sys_info;
	
};

}
#endif /* __SYSTEM_H__ */
