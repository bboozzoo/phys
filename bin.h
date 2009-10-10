#ifndef __BIN_H__
#define __BIN_H__

#include <list>
#include <cstdint>
#include "point.h"

namespace phys {

class bin
{
	public:
		bin();
		~bin();
		static uint32_t width() 
		{
			return m_width;
		}

		static uint32_t height() 
		{
			return m_height;
		}
		static void set_size(uint32_t width, uint32_t height) 
		{
			bin::m_width = width;
			bin::m_height = height;
		}
	private:
		std::list<point> m_elements;
		static uint32_t m_width;
		static uint32_t m_height;
};

}
#endif /* __BIN_H__ */
