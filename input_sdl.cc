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
uint32_t input_SDL::poll()
{
    uint32_t ret = 0;
    SDL_Event e;
    while (SDL_PollEvent(&e)) 
    {
        switch(e.type) 
        {
            case SDL_KEYDOWN:
                ret = static_cast<uint32_t>(e.key.keysym.sym);
                break;
            case SDL_QUIT:
                ret = -1; /* 0xfffff...*/
                break;
            default:
                break;
        }
    }
    return ret;
}

uint32_t input_SDL::get_ticks()
{
    return SDL_GetTicks();
}


}

