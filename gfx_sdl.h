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
	private:
		SDL_Surface * m_surface;
};

}
#endif /* __GFX_SDL_H__ */
