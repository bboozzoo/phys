#ifndef __SIM_H__
#define __SIM_H__
#include <list>
#include "system.h"
#include "gfx.h"
#include "input.h"
#include "coord.h"
#include "point.h"
#include "plane.h"
#include "bin.h"

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
        struct user_input_state
        {
            pos_t m_last_click_pos;
            bool m_last_click_valid;
        };

        struct simulation_state
        {
            simulation_state()
                : m_run(false), m_paused(false)
            {}
            ~simulation_state()
            {}

            bool m_run;
            bool m_paused;
        };

        void handle_input();
        void draw();
        void calc(double delta_ms);
        void apply_gravity(point * p, vector_t & f);
        void add_point(pos_t & initial_position, vector_t & initial_velocity);

        gfx *               m_gfx;  /* graphics */
        input *             m_input; /* input */
        std::list<point *>  m_points;
        plane               m_plane; 
        double              m_time; /* time bookkeeping */
        coord               m_coord; /* coordinate translation */
        vector_t            m_accel_gravity; /* default gravity */
        bin_set             m_bin_set;
        simulation_state    m_state; /* running flag */
        user_input_state    m_input_state;

};

}
#endif /* __SIM_H__ */
