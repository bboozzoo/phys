#ifndef __INPUT_H__
#define __INPUT_H__ 
#include <cstdint>
#include "event.h"

namespace sys
{

class input 
{
    public: 
        input() {}
        virtual ~input() {}
        virtual void poll(event & e) = 0;
        virtual uint32_t get_ticks() = 0;
};

}
#endif /* __INPUT_H__ */
