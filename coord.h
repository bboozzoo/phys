#ifndef __COORD_H__
#define __COORD_H__

#include "bin.h"

namespace phys {

class coord 
{
	public:
		coord(uint32_t n_bins_width, uint32_t n_bins_height);
		virtual ~coord();
	private:
		bin * m_bins;
};

}
#endif /* __COORD_H__ */
