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
        simulation(gfx * g, input * i);
        ~simulation();
        void setup();
        void finish();
        void run();
    private:
        void draw();
        void calc(double delta_ms);
        void apply_gravity(point * p);

        gfx * m_gfx;
        input * m_input;
        std::list<point *> m_points;
        double  m_time;
        coord m_coord;
        ublas::vector<double> m_accel_gravity;
};

}
#endif /* __SIM_H__ */
