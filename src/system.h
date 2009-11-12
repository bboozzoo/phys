#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#include <cstdint>
#include "gfx.h"
#include "input.h"

namespace sys
{

typedef enum 
{
    INIT_GFX    = 0x01,
    INIT_AUDIO  = 0x02,
    INIT_INPUT  = 0x04,
} sys_init_flags_t;

class system 
{
	public:
        
		static system * init(uint32_t sys_init_flags);
		static void finish();
        gfx * get_gfx();
        input * get_input();
        

	private:
		system(uint32_t sys_init_flags);
		~system();
	
        gfx * m_gfx;	
        input * m_input;
		static system * m_sys_single;
	
};

}
#endif /* __SYSTEM_H__ */
