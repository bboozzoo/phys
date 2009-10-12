#ifndef __BIN_H__
#define __BIN_H__
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <list>
#include <cstdint>
#include "point.h"

namespace phys {

class bin
{
	public:
		bin();
		~bin();
	private:
		std::list<point*> m_objects;

};

class bin_set
{
	public:
		bin_set();
		~bin_set();
		bin & get_bin(ublas::vector<double> & v);
	private:
};

}
#endif /* __BIN_H__ */
