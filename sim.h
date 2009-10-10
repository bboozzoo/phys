#ifndef __SIM_H__
#define __SIM_H__
#include <list>
#include "system.h"
#include "gfx.h"
#include "input.h"
#include "coord.h"
#include "point.h"

namespace phys
{

class simulation
{
    public: 
        simulation() 
            : m_gfx(NULL), m_input(NULL), m_initialized(0)
        {
        }
        ~simulation() 
        {
        }
        void setup();
        void finish();
        void run();
    private:
        void initialize();
        void draw();
        void calc();

        gfx * m_gfx;
        input * m_input;
        int m_initialized;
        std::list<point *> m_points;
        uint32_t m_time;
        coord m_coord;
};

}
#endif /* __SIM_H__ */
