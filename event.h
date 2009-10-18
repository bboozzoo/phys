#ifndef __EVENT_H__
#define __EVENT_H__
#include <boost/shared_ptr.hpp>

namespace phys
{

class event_info
{
    public:
        event_info()
        {}
        virtual ~event_info()
        {}
};

typedef boost::shared_ptr<event_info> event_info_sh_t;

class event_info_mouse : public event_info
{
    public:
        event_info_mouse(uint32_t x, uint32_t y)
            : m_x(x), m_y(y)
        {}
        ~event_info_mouse()
        {}
        uint32_t operator()(uint32_t idx) 
        {
            if (idx == 0)
                return m_x;
            return m_y;
        }

    private:
        uint32_t m_x;
        uint32_t m_y;

};

class event_info_key : public event_info
{
    public:
        event_info_key();
        ~event_info_key();
};

class event
{
	public:
		typedef enum 
		{ 
			EVENT_NONE = 0, /* empty event === no input */
			EVENT_QUIT,
			EVENT_MOUSE_MOTION,
            EVENT_MOUSE_BUTTON_DOWN,
            EVENT_MOUSE_BUTTON_UP,
			EVENT_KEY,
		} event_type_t;

		event();
		~event();
		event(const event & e);
		event_info & get_info();
		bool operator==(event_type_t etype);
        event_type_t get_type();
		void set_type(event_type_t e);
		void set_info(event_info_sh_t & e);
		void clear();
	private:
        event_info_sh_t     m_info;
		event_type_t        m_type;
};

}
#endif /* __EVENT_H__ */

