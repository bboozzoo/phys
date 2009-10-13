#ifndef __EVENT_H__
#define __EVENT_H__

namespace phys
{

class event_info
{


};

class even_info_mouse : public event_info
{

};

class event_info_key : public event_info
{

};

class event
{
	public:
		typedef enum 
		{ 
			EVENT_NONE = 0, /* empty event === no input */
			EVENT_QUIT,
			EVENT_MOUSE,
			EVENT_KEY,
		} event_type_t
		event();
		~event();
		event(const event & e);
		event_info & get_info();
		bool operator==(const event & e, event_type_t etype);
		void set_type(etype e);
		void set_info(einfo * e);
		void clear();
	private:
		event_info * m_info;
		event_type_t m_type;
};

}
#endif /* __EVENT_H__ */

