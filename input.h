#ifndef __INPUT_H__
#define __INPUT_H__ 
#include <cstdint>

namespace phys
{

class input 
{
    public: 
        input() {}
        virtual ~input() {}
        virtual uint32_t poll() = 0;
        virtual uint32_t get_ticks() = 0;


};

}
#endif /* __INPUT_H__ */
