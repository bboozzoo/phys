#include <SDL/SDL.h>
#include "gfx_sdl.h"

#define VIDEO_W 800
#define VIDEO_H 600
#define VIDEO_BPP 32

namespace phys 
{

void gfx_SDL::init() 
{
	const SDL_VideoInfo * video_info = NULL;
	SDL_Surface * surface = NULL;
	uint32_t video_flags = 0x0;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

	}

	video_info = SDL_GetVideoInfo();
	video_flags = SDL_SWSURFACE | SDL_DOUBLEBUF;
	surface = SDL_SetVideoMode(VIDEO_W, VIDEO_H, VIDEO_BPP, video_flags);

}



}
