#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "gfx_sdl.h"

#define VIDEO_W 800
#define VIDEO_H 600
#define VIDEO_BPP 32

namespace sys
{

void gfx_SDL::init() 
{
	const SDL_VideoInfo * video_info = NULL;
	uint32_t video_flags = 0x0;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

	}

	video_info = SDL_GetVideoInfo();
	video_flags = SDL_SWSURFACE | SDL_DOUBLEBUF;
	m_surface = SDL_SetVideoMode(VIDEO_W, VIDEO_H, VIDEO_BPP, video_flags);

    m_framerate.frame_cnt = 0;
    m_framerate.last_calc_time = ((double)SDL_GetTicks()) / 1000.0;
}

void gfx_SDL::update()
{
    /* show framerate */
    m_framerate.frame_cnt++;
    if (m_framerate.frame_cnt == FRAMERATE_CNT_THRESH)
    {
        uint32_t now = SDL_GetTicks();
        uint32_t diff = SDL_GetTicks() - m_framerate.last_calc_time;
        snprintf(m_framerate.rate_buf, FRAMERATE_BUF_LEN, "FPS: %.2f", (((double)FRAMERATE_CNT_THRESH) / (double) diff)* 1000.0);
        m_framerate.last_calc_time = now;
        m_framerate.frame_cnt = 0;

    }
    stringColor(m_surface, 0, 0, m_framerate.rate_buf, color::WHITE);
    SDL_Flip(m_surface);
}

void gfx_SDL::draw()
{

}

uint32_t gfx_SDL::get_width()
{
    return m_surface->w;
}

uint32_t gfx_SDL::get_height()
{
    return m_surface->h;
}
}
