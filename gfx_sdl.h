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
		SDL_Surface * m_surface;
};

}
#endif /* __GFX_SDL_H__ */
