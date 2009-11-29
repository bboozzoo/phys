#include <SDL/SDL.h>
#include <GL/gl.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "gfx_sdl.h"
#include "log.h"

#define VIDEO_W 800
#define VIDEO_H 600
#define VIDEO_BPP 32

namespace sys
{

void 
gfx_SDL::init() 
{
	const SDL_VideoInfo * video_info = NULL;
	uint32_t video_flags = 0x0;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

	}

	video_info = SDL_GetVideoInfo();
    video_flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;
    LOG(1, "video mem (kb): " << video_info->video_mem);
    if (video_info->hw_available) {
        LOG(1, "video: surface stored in HW");
        video_flags |= SDL_HWSURFACE;
    } else {
        LOG(1, "video: surface stored in SW");
        video_flags |= SDL_SWSURFACE;
    }
    
    if (video_info->blit_hw) {
        LOG(1, "video: HW accelerated blit");
        video_flags |= SDL_HWACCEL;
    } else {
        LOG(1, "video: no HW accelerated blit");
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	m_surface = SDL_SetVideoMode(VIDEO_W, VIDEO_H, VIDEO_BPP, video_flags);
    if (m_surface != NULL) {
        LOG(1, "video: initialized");
    } else {
        LOG(1, "video: init failed");
        /* throw an exception? */
    }
    initGL();

    m_framerate.frame_cnt = 0;
    m_framerate.last_calc_time = ((double)SDL_GetTicks()) / 1000.0;
}

void
gfx_SDL::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    /*glHint .. any? */
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_TEXTURE_2D);
    /*glEnable(GL_ALPHA_TEST);
      glAlphaFunc(GL_EQUAL, 1.0);*/
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, VIDEO_W, VIDEO_H, 0, 0, 1);
}

void 
gfx_SDL::update()
{
    /* show framerate */
#if 0
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
#endif
    SDL_GL_SwapBuffers();
}

void 
gfx_SDL::draw()
{

}

void 
gfx_SDL::clear() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

uint32_t 
gfx_SDL::get_width()
{
    return m_surface->w;
}

uint32_t 
gfx_SDL::get_height()
{
    return m_surface->h;
}
}
