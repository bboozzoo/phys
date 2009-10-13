#include <SDL/SDL.h>
#include "input_sdl.h"

namespace phys 
{

input_SDL::input_SDL() 
{

}
input_SDL::~input_SDL()
{
}

void
input_SDL::poll(event & e)
{
    event_type_t etype = event::EVENT_NONE;
    event_info * einfo = NULL;
    SDL_Event e;
    while (SDL_PollEvent(&e)) 
    {
        switch(e.type) 
        {
            case SDL_KEYDOWN:
                e.set_type(event::EVENT_KEY);
                ret = static_cast<uint32_t>(e.key.keysym.sym);
                break;
            case SDL_QUIT:
                e.set_type(event::EVENT_QUIT);
                break;
            default:
                break;
        }
    }
}

uint32_t 
input_SDL::get_ticks()
{
    return SDL_GetTicks();
}


}

