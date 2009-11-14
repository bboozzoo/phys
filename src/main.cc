#include <boost/program_options.hpp>
#include <iostream>
#include "system.h"
#include "prog.h"
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

    LOG(1, "init system");
    sys::system * sys = sys::system::init(sys::INIT_GFX | sys::INIT_INPUT);
    LOG(1, "init prog");
    prog p(sys);
    LOG(1, "setup objects");
    LOG(1, "run");
    p.run();
    LOG(1, "finished, cleanup");
    sys::system::finish();
    LOG(1, "all done");
	return 0;
}
