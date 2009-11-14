#ifndef __SIM_H__
#define __SIM_H__
#include <list>
#include "system.h"
#include "coord.h"
#include "world.h"
#if 0
#include "point.h"
#include "plane.h"
#include "bin.h"
#endif

class prog
{
    public: 
        prog(sys::system * sys);
        ~prog();
        void run();
    private:
        struct user_input_state
        {
            user_input_state() 
                : m_last_click_pos(2), m_last_click_valid(false)
            {}
            ~user_input_state()
            {}
            pos_t m_last_click_pos;
            bool m_last_click_valid;
        };

        struct prog_state
        {
            prog_state()
                : m_run(false), m_paused(false)
            {}
            ~prog_state()
            {}

            bool m_run;
            bool m_paused;
        };

        void loop();
        void handle_input();
        void finish();
#if 0
        void add_point(pos_t & initial_position, vector_t & initial_velocity);
#endif

        sys::system *       m_sys; /* system, gfx, input etc. */
#if 0
        std::list<point *>  m_points;
#endif
        world *             m_world;
        double              m_time; /* time bookkeeping */
        coord               m_coord; /* coordinate translation */
        prog_state          m_state; /* running flag */
        user_input_state    m_input_state;

};

#endif /* __SIM_H__ */
