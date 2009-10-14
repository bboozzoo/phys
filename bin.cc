#include "bin.h"

namespace phys
{

bin_set::bin_set()
{
}

void
bin_set::init(double bin_width, double bin_height, double width, double height)
{
    uint32_t bins_w = floor(width / bin_width) + 1;
    uint32_t bins_h = floor(height / bin_height) + 1;
}

bin_set::~bin_set()
{

}

bin &
bin_set::get_bin(ublas::vector<double> & coord)
{

}

}
