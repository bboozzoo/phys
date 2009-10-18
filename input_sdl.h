#ifndef __INPUT_SDL_H__
#define __INPUT_SDL_H__ 
#include "input.h"
#include "event.h"

namespace phys
{

class input_SDL : public input 
{
    public:
        input_SDL();
        ~input_SDL();
        void poll(event & e);
        uint32_t get_ticks();
    private:
        static event_info_sh_t create_mouse_info(uint32_t x, uint32_t y);
        static event_info_sh_t create_key_info(SDL_keysym * key);

};

}
#endif /* __INPUT_SDL_H__ */
