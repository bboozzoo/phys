#ifndef __INPUT_SDL_H__
#define __INPUT_SDL_H__ 
#include "input.h"

namespace phys
{

class input_SDL : public input 
{
    public:
        input_SDL();
        ~input_SDL();
        void poll(event & e);
        uint32_t get_ticks();

};

}
#endif /* __INPUT_SDL_H__ */
