#include <cstdlib>
#include <iostream>
#include <exception>
#include <sdbusplus/bus.hpp>
#include <experimental/filesystem>
#include "config.h"
#include "host_state_manager.hpp"

int main(int argc, char *argv[])
{
    namespace fs = std::experimental::filesystem;
	std::string node = argv[1];
    auto bus = sdbusplus::bus::new_default();

    // For now, we only have one instance of the host
    auto objPathInst = std::string{HOST_OBJPATH} + node;

    // Add sdbusplus ObjectManager.
    sdbusplus::server::manager::manager objManager(bus, objPathInst.c_str());

    phosphor::state::manager::Host manager(bus, objPathInst.c_str());

    auto dir = fs::path(HOST_STATE_PERSIST_PATH).parent_path();
    fs::create_directories(dir);

	auto busName = std::string{HOST_BUSNAME} + node;
    bus.request_name(busName.c_str());

    while (true)
    {
        bus.process_discard();
        bus.wait();
    }
    return 0;
}
