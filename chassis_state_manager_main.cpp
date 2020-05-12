#include <cstdlib>
#include <iostream>
#include <exception>
#include <sdbusplus/bus.hpp>
#include "config.h"
#include "chassis_state_manager.hpp"

int main(int argc, char *argv[])
{
    auto bus = sdbusplus::bus::new_default();
	std::string node = argv[1];

    // For now, we only have one instance of the chassis
    auto objPathInst = std::string{CHASSIS_OBJPATH} + node;

    // Add sdbusplus ObjectManager.
    sdbusplus::server::manager::manager objManager(bus, objPathInst.c_str());

    phosphor::state::manager::Chassis manager(bus, objPathInst.c_str());

	auto busName = std::string{CHASSIS_BUSNAME} + node;
    bus.request_name(busName.c_str());
    manager.startPOHCounter();

    return 0;
}
