#ifndef __GFX_SDL_H__
#define __GFX_SDL_H__
#include <SDL/SDL.h>
#include "gfx.h"

namespace phys 
{

class gfx_SDL : public gfx
{
	public:
		gfx_SDL()
		{

		}
		virtual ~gfx_SDL()
		{
		}

		virtual void init();
        virtual void update();
        virtual void draw();
        virtual uint32_t get_width();
        virtual uint32_t get_height();
        SDL_Surface * get_ctx()
        {
            return m_surface;
        }
	private:
#define FRAMERATE_BUF_LEN 10
#define FRAMERATE_CNT_THRESH 50 
        struct frame_rate
        {
            uint32_t    frame_cnt;
            uint32_t    last_calc_time; 
            char        rate_buf[FRAMERATE_BUF_LEN];
        };
		SDL_Surface *   m_surface;
        frame_rate      m_framerate;
};

}
#endif /* __GFX_SDL_H__ */
