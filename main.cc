#include <boost/program_options.hpp>
#include <iostream>
#include "system.h"
#include "sim.h"
#include "log.h"

using namespace boost;
int main (int argc, char * argv[]) {
    uint32_t req_level = 0;
    program_options::variables_map vm;
    program_options::options_description desc("Allowed options");

    desc.add_options()
        ("help,h", "Show help")
        ("log,l", program_options::value<uint32_t>(&req_level), "Logging level")
        ;

    program_options::store(program_options::parse_command_line(argc, argv, desc), vm);
    program_options::notify(vm);

    if (vm.count("help") > 0)
    {
        std::cout << desc << std::endl;
        return 1;
    }
    
    log_level = req_level;

	phys::system::init(phys::system::INIT_GFX | phys::system::INIT_INPUT);

    phys::simulation sim(phys::system::get_gfx(), phys::system::get_input());
    sim.setup();
    sim.run();
    sim.finish();
	return 0;
}
