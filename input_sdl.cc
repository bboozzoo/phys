#include <SDL/SDL.h>
#include "input_sdl.h"
#include "log.h"

namespace phys 
{

input_SDL::input_SDL() 
{

}
input_SDL::~input_SDL()
{
}

void
input_SDL::poll(event & ev)
{
    event::event_type_t etype = event::EVENT_NONE;
    boost::shared_ptr<event_info> einfo;
    SDL_Event sdl_ev;

    while (SDL_PollEvent(&sdl_ev)) 
    {
        switch(sdl_ev.type) 
        {
            case SDL_KEYDOWN:
                LOG(1, "event key: " << sdl_ev.key.keysym.sym);
                etype = event::EVENT_KEY;
                /*ret = static_cast<uint32_t>(sdl_ev.key.keysym.sym);*/
                break;
            case SDL_MOUSEMOTION:
                etype = event::EVENT_MOUSE_MOTION;
                einfo = create_mouse_info(sdl_ev.motion.x, sdl_ev.motion.y);
                LOG(1, "event mouse motion: " << sdl_ev.motion.x << "," << sdl_ev.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                if (sdl_ev.type == SDL_MOUSEBUTTONDOWN)
                    etype = event::EVENT_MOUSE_BUTTON_DOWN;
                else
                    etype = event::EVENT_MOUSE_BUTTON_UP;
                einfo = create_mouse_info(sdl_ev.button.x, sdl_ev.button.y);
                LOG(1, "event mouse button: " << sdl_ev.button.x << "," << sdl_ev.button.y);
                break;
            case SDL_QUIT:
                etype = event::EVENT_QUIT;
                LOG(1, "event quit");
                break;
            default:
                break;
        }
    }
    ev.set_type(etype);
    ev.set_info(einfo);
}

uint32_t 
input_SDL::get_ticks()
{
    return SDL_GetTicks();
}

event_info_sh_t 
input_SDL::create_mouse_info(uint32_t x, uint32_t y)
{
    event_info_mouse * e = new event_info_mouse(x, y);
    event_info_sh_t ei(e);
    return ei;
}

}

